cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_FIND_LIBRARY_SUFFIXES)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .so .a)
endif ()
if(NOT CMAKE_FIND_LIBRARY_PREFIXES)
    set(CMAKE_FIND_LIBRARY_PREFIXES "lib")
endif ()

set(IMGUI_DIR libs/imgui)
set(gRPC_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/grpc)

find_package(OpenSSL REQUIRED)
find_package(Protobuf REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(gRPC CONFIG REQUIRED)

add_subdirectory(libs/PcapPlusPlus-25.05)
add_subdirectory(utils)
add_subdirectory(ui)
add_subdirectory(core)
add_subdirectory(grpc-interface)

add_library(imgui
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

pkg_search_module(GLFW REQUIRED glfw3)


target_include_directories(imgui
        PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
)






include_directories(${CMAKE_SOURCE_DIR}/src)





# Copy after build

