
add_subdirectory(PcapPlusPlus-25.05)
add_library(AshkanTool-Core
        interface.cpp
        interface.h
        src/net_core.cpp
        include/net_core.h
        src/logger.cpp
        include/logger.h
)
target_link_libraries(AshkanTool-Core
        PUBLIC
            Pcap++ Packet++ Common++
)