cmake_minimum_required(VERSION 3.30)
project(AshkanTool)

set(CMAKE_CXX_STANDARD 20)


add_executable(AshkanTool main.cpp)

add_subdirectory(ui)
add_subdirectory(model)


target_link_libraries(AshkanTool
        PRIVATE
        AshkanTool-ui
        AshkanTool-Core
)