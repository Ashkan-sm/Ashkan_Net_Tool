cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 20)




add_library(AshkanTool-ui
        imgui-ui.cpp
        imgui-ui.hpp
        windows/main-window.cpp
        windows/imgui-headers.hpp
        windows/main-window.hpp
        config.h
        windows/sub-window.cpp
        windows/sub-window.hpp)

target_include_directories(AshkanTool-ui
        PUBLIC
        .
        ${GLFW_INCLUDE_DIRS}
        ../..

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
        GL
)
