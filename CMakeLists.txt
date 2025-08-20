cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

if(NOT CMAKE_FIND_LIBRARY_SUFFIXES)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .so .a)
endif ()
if(NOT CMAKE_FIND_LIBRARY_PREFIXES)
    set(CMAKE_FIND_LIBRARY_PREFIXES "lib")
endif ()

project(AshkanTool)

add_subdirectory(src)

add_executable(AshkanTool src/main.cpp)

target_include_directories(AshkanTool
        PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AshkanTool
        PUBLIC
        AshkanTool-ui
        AshkanTool-Core
        Pcap++ Packet++ Common++
        utils
)

set(RESOURCE_SRC_DIR "${CMAKE_SOURCE_DIR}/resource")
set(RESOURCE_DST_DIR "${CMAKE_BINARY_DIR}/ui-resource")
add_custom_command(
        TARGET AshkanTool POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCE_SRC_DIR}" "${RESOURCE_DST_DIR}"
        COMMENT "Copying subproject resources to build directory"
)