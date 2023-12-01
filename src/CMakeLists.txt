set(
    CS102_FINAL_PROJ_SRC
    "./board.cpp"
    "./logic_controller.cpp"
    "./main.cpp"
    "./ui_controller.cpp"
)

add_executable(CS102_FINAL_PROJ ${CS102_FINAL_PROJ_SRC})

target_link_libraries(CS102_FINAL_PROJ PRIVATE glfw libglew_static)
