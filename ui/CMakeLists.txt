cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)




add_library(AshkanTool-ui
        imgui-ui.cpp
        imgui-ui.hpp
        src/main-window.cpp
        include/imgui-headers.hpp
        include/main-window.hpp
        config.h
        src/sub-window.cpp
        include/sub-window.hpp)

target_include_directories(AshkanTool-ui
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${GLFW_INCLUDE_DIRS}
)

target_link_libraries(AshkanTool-ui
        imgui
        ${GLFW_LIBRARIES}
        dl
        pthread
        GL
        AshkanTool-Core
)

add_executable(UiHelp ../libs/imgui/examples/example_glfw_opengl3/main.cpp)
target_link_libraries(UiHelp         imgui
        ${GLFW_LIBRARIES}
        dl
        pthread
        GL)

