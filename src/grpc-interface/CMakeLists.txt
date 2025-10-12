set(PROTO_FILES
        proto/ui-services.proto
)

set(PROTO_SRCS "")
set(PROTO_HDRS "")

foreach(proto ${PROTO_FILES})
    get_filename_component(proto_name ${proto} NAME_WE)

    set(proto_src "${CMAKE_CURRENT_BINARY_DIR}/proto/${proto_name}.pb.cc")
    set(proto_hdr "${CMAKE_CURRENT_BINARY_DIR}/proto/${proto_name}.pb.h")
    set(grpc_src "${CMAKE_CURRENT_BINARY_DIR}/proto/${proto_name}.grpc.pb.cc")
    set(grpc_hdr "${CMAKE_CURRENT_BINARY_DIR}/proto/${proto_name}.grpc.pb.h")

    add_custom_command(
            OUTPUT ${proto_src} ${proto_hdr} ${grpc_src} ${grpc_hdr}
            COMMAND ${Protobuf_PROTOC_EXECUTABLE}
            ARGS --grpc_out=${CMAKE_CURRENT_BINARY_DIR}
            --cpp_out=${CMAKE_CURRENT_BINARY_DIR}
            --plugin=protoc-gen-grpc=/usr/bin/grpc_cpp_plugin
            -I ${CMAKE_CURRENT_SOURCE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/${proto}
            DEPENDS ${proto}
            COMMENT "Generating ${proto_name} protobuf and gRPC sources"
    )

    list(APPEND PROTO_SRCS ${proto_src} ${grpc_src})
    list(APPEND PROTO_HDRS ${proto_hdr} ${grpc_hdr})
endforeach()

# Make a custom target so files are generated before build
add_custom_target(generate_protos ALL DEPENDS ${PROTO_SRCS} ${PROTO_HDRS})

# Build the library
add_library(grpc_interface ${PROTO_SRCS} ${PROTO_HDRS}
        c-lient-interface.cpp
        c-lient-interface.hpp
        server-interface.cpp
        server-interface.hpp
        services.cpp
        services.hpp)



add_dependencies(grpc_interface generate_protos)
target_include_directories(grpc_interface PUBLIC
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}/proto
        ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(grpc_interface PUBLIC
        gRPC::grpc++
        protobuf::libprotobuf
        AshkanTool-Core)
