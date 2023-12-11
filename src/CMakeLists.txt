set(
    CS102_FINAL_PROJ_SRC
    "./board.cpp"
    "./buffer.cpp"
    "./logic_controller.cpp"
    "./main.cpp"
    "./shader.cpp"
    "./texture.cpp"
    "./time_util.cpp"
    "./ui_controller.cpp"
    "./vtx_array.cpp"
    "./window.cpp"
)

add_executable(CS102_FINAL_PROJ ${CS102_FINAL_PROJ_SRC})

target_link_libraries(CS102_FINAL_PROJ PRIVATE glfw libglew_static glm::glm soil2)
