cmake_minimum_required(VERSION 3.30)

set(IMGUI_DIR libs/imgui)
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


project(AshkanTool)
target_include_directories(imgui
        PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)
set(CMAKE_CXX_STANDARD 20)
add_subdirectory(libs/PcapPlusPlus-25.05)

add_executable(AshkanTool main.cpp)

add_subdirectory(ui)
add_subdirectory(core)


target_link_libraries(AshkanTool
        PUBLIC
        AshkanTool-ui
        AshkanTool-Core

        Pcap++ Packet++ Common++
)
set(RESOURCE_SRC_DIR "${CMAKE_SOURCE_DIR}/ui/resource")
set(RESOURCE_DST_DIR "${CMAKE_BINARY_DIR}/ui-resource")

# Copy after build
add_custom_command(
        TARGET AshkanTool POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCE_SRC_DIR}" "${RESOURCE_DST_DIR}"
        COMMENT "Copying subproject resources to build directory"
)