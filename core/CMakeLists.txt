
find_package(OpenSSL REQUIRED)

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
        src/task/tasks/dtp-domain-extraction-task.cpp
        src/task/tasks/dtp-domain-extraction-task.hpp
        "src/task/tasks/task-headers.hpp"
        src/packet_receiver/recievers/mitm-forwarding.cpp
        src/packet_receiver/recievers/arp-poison-detection.cpp
        src/packet_receiver/recievers/vlan-hopping.cpp
        src/packet_receiver/recievers/dtp-domain-extraction.cpp
        src/data_holders/wifi.hpp
        src/task/tasks/wifi-ap-scanning-task.cpp
        src/task/tasks/wifi-ap-scanning-task.hpp
        src/packet_receiver/recievers/wifi-ap-scanning.cpp
        src/task/tasks/wifi-host-scanning-task.cpp
        src/task/tasks/wifi-host-scanning-task.hpp
        src/packet_receiver/recievers/wifi-host-scanning.cpp
        src/task/tasks/deauth-packet-sending.cpp
        src/task/tasks/deauth-packet-sending.hpp
        src/task/tasks/wpa-2-hand-shake-capture-task.cpp
        src/task/tasks/wpa-2-hand-shake-capture-task.hpp
        src/packet_receiver/recievers/wpa2-handshake-capturing.cpp
        src/task/tasks/wifi-password-cracking-task.cpp
        src/task/tasks/wifi-password-cracking-task.hpp
        src/task/tasks/wpa-2-cracking-thread.cpp
        src/task/tasks/wpa-2-cracking-thread.hpp
)



target_include_directories(AshkanTool-Core
        PUBLIC
        src/data_holders
)
target_link_libraries(AshkanTool-Core
        PUBLIC
        Pcap++ Packet++ Common++
        OpenSSL::Crypto
)