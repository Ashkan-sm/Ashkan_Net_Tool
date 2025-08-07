cmake_minimum_required(VERSION 3.18)
find_package(OpenSSL REQUIRED)
message(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")

add_library(AshkanTool-Core
        data-holders/wifi.hpp
        packet-receiver/packet-receiver.hpp
        packet-receiver/recievers/mitm-forwarding.cpp
        packet-receiver/recievers/arp-poison-detection.cpp
        packet-receiver/recievers/vlan-hopping.cpp
        packet-receiver/recievers/dtp-domain-extraction.cpp


        capture-wrapper.cpp
        capture-wrapper.hpp
        task/task.cpp
        task/task.hpp
        task/tasks/arp-poisoning-task.cpp
        task/tasks/arp-poisoning-task.hpp
        task/tasks/arp-poison-detection-task.cpp
        task/tasks/arp-poison-detection-task.hpp
        task/tasks/vlan-hopping-task.cpp
        task/tasks/vlan-hopping-task.hpp
        task/tasks/mitm-packet-forwarding.cpp
        task/tasks/mitm-packet-forwarding.hpp
        task/tasks/dtp-negotiation.cpp
        task/tasks/dtp-negotiation.hpp
        task/tasks/dtp-domain-extraction-task.cpp
        task/tasks/dtp-domain-extraction-task.hpp


        task/tasks/wifi-ap-scanning-task.cpp
        task/tasks/wifi-ap-scanning-task.hpp
        packet-receiver/recievers/wifi-ap-scanning.cpp
        task/tasks/wifi-host-scanning-task.cpp
        task/tasks/wifi-host-scanning-task.hpp
        packet-receiver/recievers/wifi-host-scanning.cpp
        task/tasks/deauth-packet-sending.cpp
        task/tasks/deauth-packet-sending.hpp
        task/tasks/wpa-2-hand-shake-capture-task.cpp
        task/tasks/wpa-2-hand-shake-capture-task.hpp
        packet-receiver/recievers/wpa2-handshake-capturing.cpp
        task/tasks/wifi-password-cracking-task.cpp
        task/tasks/wifi-password-cracking-task.hpp
        task/tasks/wpa-2-cracking-thread.cpp
        task/tasks/wpa-2-cracking-thread.hpp
        net-core.cpp
        net-core.hpp
        interface.cpp
        interface.hpp
)

target_include_directories(AshkanTool-Core
        PUBLIC
        ${CMAKE_SOURCE_DIR/src}
)

target_link_libraries(AshkanTool-Core
        PUBLIC
        Pcap++ Packet++ Common++
        OpenSSL::Crypto
        utils
)

