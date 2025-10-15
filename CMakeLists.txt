cmake_minimum_required(VERSION 3.18)
project(AshkanTool)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wno-error=restrict)

find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

if(NOT CMAKE_FIND_LIBRARY_SUFFIXES)
    set(CMAKE_FIND_LIBRARY_SUFFIXES .so .a)
endif ()
if(NOT CMAKE_FIND_LIBRARY_PREFIXES)
    set(CMAKE_FIND_LIBRARY_PREFIXES "lib")
endif ()


add_subdirectory(src)

add_executable(AshkanTool-Server src/server.cpp)
add_executable(AshkanTool-Client src/client.cpp)


target_include_directories(AshkanTool-Server
        PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)
target_include_directories(AshkanTool-Client
        PUBLIC
        ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(AshkanTool-Server
        PUBLIC
        AshkanTool-Core
        Pcap++ Packet++ Common++
        utils
        ${Protobuf_LIBRARIES}  # This is crucial
        grpc_interface
)
target_link_libraries(AshkanTool-Client
        PUBLIC
        AshkanTool-ui
        Pcap++ Packet++ Common++
        utils
        grpc_interface

)

set(RESOURCE_SRC_DIR "${CMAKE_SOURCE_DIR}/resource")
set(RESOURCE_DST_DIR "${CMAKE_BINARY_DIR}/ui-resource")
add_custom_command(
        TARGET AshkanTool-Client POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${RESOURCE_SRC_DIR}" "${RESOURCE_DST_DIR}"
        COMMENT "Copying subproject resources to build directory"
)
