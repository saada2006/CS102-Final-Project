#include "ui_controller.h"

#include "board.h"
#include "text_box.h"

#include <GL/glew.h>

#include <iostream>

bool glew_already_init = false;
UIController::UIController() : _last_input(MOV_NONE), _width(1280), _height(720) {
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

    _background_color = glm::vec3(0.9, 0.9, 0.8);

    _tile_shader.CompileFiles("./res/shaders/tile.vert", "./res/shaders/tile.frag");
    _tile_scale = 0.8;
    _tile_color = glm::vec3(0.8, 0.8, 0.7);


    float horizontal = 1.0;
    float vertical = (horizontal * _height) / _width;

    float tile_prescale = 0.5f;
    glm::vec2 tile_offset = glm::vec2(-0.5, 0.0);
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

void UIController::render_board(const Board& board) {
    // render and swap buffers
    /*
    std::cout << "\n\n\n";
    for(int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            std::cout << board._num[i][j] << '\t';
        }
        std::cout << '\n';
    }
    std::cout.flush();
    */
    glClearColor(_background_color.r, _background_color.y, _background_color.z, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);

    Buffer tile_buf;
    VertexArray tile_arr;
    tile_arr.CreateBinding();
    int n_tile_triangles = gen_tiles(tile_arr, tile_buf);
    _tile_shader.CreateBinding();
    _tile_shader.LoadVector3F32("tile_color", _tile_color);
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
            tbox.gen_vtx_array(text, offset, 0.2);

            tbox._vtx_arr.CreateBinding();
            _bitmap_shader.CreateBinding();
            _bitmap_shader.LoadMat4x4F32("tile_transform", _tile_transform);
            _bitmap_shader.LoadTexture2D("bitmap", _bitmap_font);
            glDrawArrays(GL_TRIANGLES, 0, tbox._num_triangles);
            tbox.free();
        }
    }

    std::cout << glGetError() << std::endl;

    _window.update_screen();
    _window.update_poll_events();
}

MovementInput UIController::poll_user_input() {
    MovementInput implied_input = MOV_NONE;

    MovementInput current_input = poll_current_input();
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

            float adjusted_scale = _tile_scale / BOARD_SIZE;
            for(auto& v : tile_base) {
                tiles.push_back(adjusted_scale * v + offset);
            }

        }
    }

    tile_buf.UploadData(tiles, GL_STATIC_DRAW);

    tile_arr.CreateStream(0, 2, 0);

    if(!tform_dump) {
        for(auto& v : tiles) {
            glm::vec4 gl_Position = _tile_transform * glm::vec4(v, 0.5f, 1.0f);
            std::cout << gl_Position.x << '\t' << gl_Position.y << '\t' << gl_Position.z << '\t' << gl_Position.w << '\n';
        }
        tform_dump = true;
    }
    std::cout.flush();

    return tiles.size();
}   

MovementInput UIController::poll_current_input() {
    if(_window.get_key(GLFW_KEY_W)) {
        return MOV_U;
    } else if(_window.get_key(GLFW_KEY_S)) {
        return MOV_D;
    } else if(_window.get_key(GLFW_KEY_D)) {
        return MOV_R;
    } else if(_window.get_key(GLFW_KEY_A)) {
        return MOV_L;
    } else {
        return MOV_NONE;
    }
}