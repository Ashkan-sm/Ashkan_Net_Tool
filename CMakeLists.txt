cmake_minimum_required(VERSION 3.30)
project(AshkanTool)

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
add_executable(AshkanTool main.cpp)

target_include_directories(imgui PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)
target_include_directories(AshkanTool PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(AshkanTool ${GLFW_LIBRARIES} dl pthread GL)

add_subdirectory(PcapPlusPlus-25.05)

target_link_libraries(AshkanTool
        Pcap++ Packet++ Common++ imgui
)
