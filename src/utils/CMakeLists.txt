cmake_minimum_required(VERSION 3.18)
set(CMAKE_CXX_STANDARD 20)
add_library(utils STATIC
        logger.cpp
        net-utils.cpp
)

target_include_directories(utils PUBLIC ${CMAKE_SOURCE_DIR}/src)

target_link_libraries(utils
        PUBLIC
        Pcap++ Packet++ Common++
)