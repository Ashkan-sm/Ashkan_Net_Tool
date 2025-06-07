

add_library(AshkanTool-Core
        interface.cpp
        interface.hpp
        src/net-core.cpp
        include/net-core.hpp
        src/logger.cpp
        include/logger.hpp
        src/packet-receiver.cpp
        include/packet-receiver.hpp
        src/capture-wrapper.cpp
        include/capture-wrapper.hpp
        utils/task.cpp
        utils/task.hpp
)
target_link_libraries(AshkanTool-Core
        PUBLIC

        Pcap++ Packet++ Common++
)