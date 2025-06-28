

add_library(AshkanTool-Core
        interface.cpp
        interface.hpp
        src/net-core.cpp
        src/net-core.hpp
        ../utils/logger.cpp
        ../utils/logger.hpp
        src/packet-receiver.cpp
        src/packet-receiver.hpp
        src/capture-wrapper.cpp
        src/capture-wrapper.hpp
        src/Task/task.cpp
        src/Task/task.hpp
        src/Task/tasks/arp-poisoning-task.cpp
        src/Task/tasks/arp-poisoning-task.hpp
        ../utils/net-utils.cpp
        ../utils/net-utils.hpp
        src/Task/tasks/arp-poison-detection-task.cpp
        src/Task/tasks/arp-poison-detection-task.hpp
        src/Task/tasks/vlan-hopping-task.cpp
        src/Task/tasks/vlan-hopping-task.hpp
        src/Task/tasks/mitm-packet-forwarding.cpp
        src/Task/tasks/mitm-packet-forwarding.hpp
)
target_link_libraries(AshkanTool-Core
        PUBLIC

        Pcap++ Packet++ Common++
)