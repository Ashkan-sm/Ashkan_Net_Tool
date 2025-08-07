//
// Created by dev on 6/5/25.
//

#ifndef ASHKANTOOL_PACKET_RECEIVER_HPP
#define ASHKANTOOL_PACKET_RECEIVER_HPP

#include <iostream>
#include <map>

#include <netinet/in.h>

#include "IPLayer.h"
#include "EthDot3Layer.h"
#include "LLCLayer.h"
#include "VlanLayer.h"
#include "PayloadLayer.h"

#include "utils/logger.hpp"
#include "core/task/task.hpp"
#include "core/data-holders/wifi.hpp"

namespace ashk {

    struct ArpPoisoningDetectionCookie {
        std::map<pcpp::IPv4Address, std::vector<pcpp::MacAddress>> ip_mac_map;
    };
    struct VlanHoppingCookie {
        int inner_id;
        int outer_id;
    };
    struct WifiApScanningCookie {
        std::vector<WifiAp> *ap_list;
    };
    struct WifiHostScanningCookie {
        std::vector<std::shared_ptr<WifiHost>> *host_list;
    };
    struct MITMForwardingCookie {
        pcpp::IPv4Address victim_ip;
        pcpp::MacAddress victim_mac;
        pcpp::IPv4Address gateway_ip;
        pcpp::MacAddress gateway_mac;
    };
    struct DTPDomainExtractionCookie {
        char* buffer= nullptr;
        Task* task= nullptr;
    };
    struct WPA2HandShakeCapturingCookie {
        std::shared_ptr<HandShakeData> hand_shake_data= nullptr;
        Task* task= nullptr;
    };
    class PacketReceiver {
    public:
        static void onPacketArrivesArpPoisoningDetection(pcpp::RawPacket *raw_packet, pcpp::PcapLiveDevice *dev, void *cookie);
        static void onPacketArrivesVlanHopping(pcpp::RawPacket *raw_packet, pcpp::PcapLiveDevice *dev, void *cookie);
        static void onPacketArrivesMITMForwarding(pcpp::RawPacket *raw_packet, pcpp::PcapLiveDevice *dev, void *cookie);
        static void onPacketArrivesDTPDomainExtraction(pcpp::RawPacket *raw_packet, pcpp::PcapLiveDevice *dev, void *cookie);
        static void onPacketArrivesWifiApScanning(pcpp::RawPacket *raw_pcap_packet, pcpp::PcapLiveDevice *dev, void *cookie);
        static void onPacketArrivesWifiHostScanning(pcpp::RawPacket *raw_pcap_packet, pcpp::PcapLiveDevice *dev, void *cookie);
        static void onPacketArrivesWPA2HandShakeCapturing(pcpp::RawPacket *raw_pcap_packet, pcpp::PcapLiveDevice *dev, void *cookie);
    };


}

#endif //ASHKANTOOL_PACKET_RECEIVER_HPP
