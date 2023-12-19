#include "ui_controller.h"

#include "board.h"
#include "text_box.h"

#include <GL/glew.h>

#include <iostream>

//#define CONSOLE_DEBUG_BOARD
//#define CONSOLE_DUMP_TFORM

const glm::vec3 BACKGROUND_COLOR(0.9, 0.9, 0.8);

const float TILE_SCALE = 0.8;
const glm::vec3 TILE_COLOR(0.8, 0.8, 0.7);

const float FONT_SCALE = 0.2;

const glm::vec2 GAME_OVER_FONT_SCALE(0.2, 0.2);

bool glew_already_init = false;
UIController::UIController() : _last_input(UINPUT_NONE), _width(1280), _height(720) {
    _window.open("2048: The Game", _width, _height, false);

    if(!glew_already_init && glewInit() != GLEW_OK) {
        std::cerr << "GLEW INITIATION FAILED!";
        abort();
    }

    glew_already_init = true;

    const uint8_t* vendor = glGetString(GL_VENDOR); // Returns the vendor
    const uint8_t* renderer = glGetString(GL_RENDERER); // Returns a hint to the model

    std::cout << "Vendor:\t" << vendor << '\n';
    std::cout << "Renderer:\t" << renderer << '\n';

    _tile_shader.CompileFiles("./res/shaders/tile.vert", "./res/shaders/tile.frag");

    float horizontal = 1.0;
    float vertical = (horizontal * _height) / _width;

    // TODO: support dynamic transform with changing resolution
    float tile_prescale = 0.5f;
    glm::vec2 tile_offset = glm::vec2(-0.9, 0.0);
    glm::mat4 pretransform = glm::scale(glm::mat4(1.0f), glm::vec3(tile_prescale, tile_prescale, 1.0f));
    pretransform = glm::translate(pretransform, glm::vec3(tile_offset, 0.0f));

    _tile_transform = glm::ortho(-horizontal, horizontal, -vertical, vertical, -0.1f, -1.0f) * pretransform;

    _bitmap_shader.CompileFiles("./res/shaders/bitmap.vert", "./res/shaders/bitmap.frag");
    _bitmap_font.CreateBinding();
    _bitmap_font.LoadTexture("./res/textures/lazy_font.png");

    glEnable(GL_BLEND);  
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
}

UIController::~UIController() {
    _window.close();
}


void UIController::render_game(const Board& board, GameState game_state) {
    // render and swap buffers
    #ifdef CONSOLE_DEBUG_BOARD
    std::cout << "\n\n\n";
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            std::cout << board._num[i][j] << '\t';
        }
        std::cout << '\n';
    }
    std::cout.flush();
    #endif

    glClearColor(BACKGROUND_COLOR.r, BACKGROUND_COLOR.y, BACKGROUND_COLOR.z, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    Buffer tile_buf;
    VertexArray tile_arr;
    tile_arr.CreateBinding();
    int n_tile_triangles = gen_tiles(tile_arr, tile_buf);
    _tile_shader.CreateBinding();
    _tile_shader.LoadVector3F32("tile_color", TILE_COLOR);
    _tile_shader.LoadMat4x4F32("tile_transform", _tile_transform);
    glDrawArrays(GL_TRIANGLES, 0, n_tile_triangles);
    tile_arr.Free();
    tile_buf.Free();

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            auto offset = get_tile_offset(i, j);
            //offset.y = -offset.y;

            std::string text = std::to_string(board._num[j][i]);

            TextBox tbox;
            tbox.gen_vtx_array(text, offset, FONT_SCALE);

            tbox._vtx_arr.CreateBinding();
            _bitmap_shader.CreateBinding();
            _bitmap_shader.LoadMat4x4F32("tile_transform", _tile_transform);
            _bitmap_shader.LoadTexture2D("bitmap", _bitmap_font);
            glDrawArrays(GL_TRIANGLES, 0, tbox._num_triangles);
            tbox.free();
        }
    }

    if(game_state != GAME_STATE_IN_PROGRESS) {
        std::string text = (game_state == GAME_STATE_WON ? "You won!" : "You lost,\nskill issue");


        glm::vec2 offset = (game_state == GAME_STATE_WON ? glm::vec2(1.8, 0.0): glm::vec2(3.0, 0.0));

        TextBox tbox;
        tbox.gen_vtx_array(text, offset, GAME_OVER_FONT_SCALE);

        tbox._vtx_arr.CreateBinding();
        _bitmap_shader.CreateBinding();
        _bitmap_shader.LoadMat4x4F32("tile_transform", _tile_transform);
        _bitmap_shader.LoadTexture2D("bitmap", _bitmap_font);
        glDrawArrays(GL_TRIANGLES, 0, tbox._num_triangles);
        tbox.free();
    }

    if(GLenum err = glGetError() != GL_NO_ERROR) {
        std::cout << err << std::endl;
        abort();
    }

    _window.update_screen();
    _window.update_poll_events();

    if(_window.get_key(GLFW_KEY_ESCAPE)) {
        _window.close();
    }
}

UserInput UIController::poll_user_input() {
    UserInput implied_input = UINPUT_NONE;

    UserInput current_input = poll_current_input();
    if(current_input != _last_input) {
        implied_input = current_input;
    }
    _last_input = current_input;

    return implied_input;
}


bool UIController::window_open() {
    return !_window.should_close();
}

glm::vec2 UIController::get_tile_offset(int i, int j) {
    glm::vec2 offset = vec2(i + 0.5f, j + 0.5f) / (float)BOARD_SIZE;
    offset = offset * 2.0f - 1.0f;

    return offset;
}


bool tform_dump = false;
int UIController::gen_tiles(VertexArray& tile_arr, Buffer& tile_buf) {
    tile_buf.CreateBinding(BUFFER_TARGET_ARRAY);
    
    std::vector<glm::vec2> tile_base = {
        {-1.0f, -1.0f},
        { 1.0f, -1.0f},
        { 1.0f,  1.0f},
        { 1.0f,  1.0f},
        {-1.0f,  1.0f},
        {-1.0f, -1.0f},
    };

    std::vector<glm::vec2> tiles;

    for(int i = 0; i < BOARD_SIZE; i++) {
        for(int j = 0; j < BOARD_SIZE; j++) {
            glm::vec2 offset = get_tile_offset(i, j);

            float adjusted_scale = TILE_SCALE / BOARD_SIZE;
            for(auto& v : tile_base) {
                tiles.push_back(adjusted_scale * v + offset);
            }

        }
    }

    tile_buf.UploadData(tiles, GL_STATIC_DRAW);

    tile_arr.CreateStream(0, 2, 0);

    #ifdef CONSOLE_DUMP_TFORM
    if(!tform_dump) {
        for(auto& v : tiles) {
            glm::vec4 gl_Position = _tile_transform * glm::vec4(v, 0.5f, 1.0f);
            std::cout << gl_Position.x << '\t' << gl_Position.y << '\t' << gl_Position.z << '\t' << gl_Position.w << '\n';
        }
        tform_dump = true;
    }
    std::cout.flush();
    #endif

    return tiles.size();
}   

UserInput UIController::poll_current_input() {
    if(_window.get_key(GLFW_KEY_W)) {
        return UINPUT_MOVE_UP;
    } else if(_window.get_key(GLFW_KEY_S)) {
        return UINPUT_MOVE_DOWN;
    } else if(_window.get_key(GLFW_KEY_D)) {
        return UINPUT_MOVE_RIGHT;
    } else if(_window.get_key(GLFW_KEY_A)) {
        return UINPUT_MOVE_LEFT;
    } else if(_window.get_key(GLFW_KEY_R)) {
        return UINPUT_RESET;
    } else {
        return UINPUT_NONE;

    }

}