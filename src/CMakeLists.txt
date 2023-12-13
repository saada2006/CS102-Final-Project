set(
    GAME_SRC
    "./board.cpp"
    "./buffer.cpp"
    "./logic_controller.cpp"
    "./main.cpp"
    "./shader.cpp"
    "./text_box.cpp"
    "./texture.cpp"
    "./time_util.cpp"
    "./ui_controller.cpp"
    "./vtx_array.cpp"
    "./window.cpp"
)

add_executable(Game2048 ${GAME_SRC})

target_link_libraries(Game2048 PRIVATE glfw libglew_static glm::glm soil2)
