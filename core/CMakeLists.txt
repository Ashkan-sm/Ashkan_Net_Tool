

add_library(AshkanTool-Core
        interface.cpp
        interface.hpp
        src/net-core.cpp
        src/net-core.hpp
        ../utils/logger.cpp
        ../utils/logger.hpp
        src/packet_receiver/packet-receiver.hpp
        src/capture-wrapper.cpp
        src/capture-wrapper.hpp
        src/task/task.cpp
        src/task/task.hpp
        src/task/tasks/arp-poisoning-task.cpp
        src/task/tasks/arp-poisoning-task.hpp
        ../utils/net-utils.cpp
        ../utils/net-utils.hpp
        src/task/tasks/arp-poison-detection-task.cpp
        src/task/tasks/arp-poison-detection-task.hpp
        src/task/tasks/vlan-hopping-task.cpp
        src/task/tasks/vlan-hopping-task.hpp
        src/task/tasks/mitm-packet-forwarding.cpp
        src/task/tasks/mitm-packet-forwarding.hpp
        src/task/tasks/dtp-negotiation.cpp
        src/task/tasks/dtp-negotiation.hpp
        src/task/tasks/dtp-domain-extraction.cpp
        src/task/tasks/dtp-domain-extraction.hpp
        "src/task/tasks/task-headers.hpp"
        src/packet_receiver/recievers/mitm-forwarding.cpp
        src/packet_receiver/recievers/arp-poison-detection.cpp
        src/packet_receiver/recievers/vlan-hopping.cpp
)
target_link_libraries(AshkanTool-Core
        PUBLIC

        Pcap++ Packet++ Common++
)