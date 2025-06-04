
add_subdirectory(PcapPlusPlus-25.05)
add_library(AshkanTool-Core
        interface.cpp
        interface.h
 )
target_link_libraries(AshkanTool-Core
        Pcap++ Packet++ Common++
)