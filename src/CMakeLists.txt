cmake_minimum_required(VERSION 3.18)
if(NOT CMAKE_FIND_LIBRARY_SUFFIXES)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .so .a)
endif ()
if(NOT CMAKE_FIND_LIBRARY_PREFIXES)
    set(CMAKE_FIND_LIBRARY_PREFIXES "lib")
endif ()
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
#pkg_search_module(GLFW REQUIRED glfw3)


target_include_directories(imgui
        PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)


set(CMAKE_CXX_STANDARD 20)
add_subdirectory(libs/PcapPlusPlus-25.05)
add_subdirectory(utils)
add_subdirectory(ui)
add_subdirectory(core)


include_directories(${CMAKE_SOURCE_DIR}/src)





# Copy after build

