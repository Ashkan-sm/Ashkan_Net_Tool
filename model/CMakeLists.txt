
add_subdirectory(PcapPlusPlus-25.05)
add_library(AshkanTool-Core
        interface.cpp
        interface.h
        src/net_core.cpp
        include/net_core.h
        src/logger.cpp
        include/logger.h
        src/packet_receiver.cpp
        include/packet_receiver.h
        src/capture_wrapper.cpp
        include/capture_wrapper.h
)
target_link_libraries(AshkanTool-Core
        PUBLIC
            Pcap++ Packet++ Common++
)