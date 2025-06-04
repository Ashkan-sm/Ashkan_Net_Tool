cmake_minimum_required(VERSION 3.30)

set(CMAKE_CXX_STANDARD 20)
set(IMGUI_DIR imgui)
add_library(imgui
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

add_library(AshkanTool-ui
        imgui_ui.cpp
        imgui_ui.h)

target_include_directories(AshkanTool-ui
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${GLFW_INCLUDE_DIRS}
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)

target_link_libraries(AshkanTool-ui
        imgui
        ${GLFW_LIBRARIES}
        dl
        pthread
        GL
)

