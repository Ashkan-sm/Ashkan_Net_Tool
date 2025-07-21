//
// Created by dev on 6/5/25.
//

#ifndef ASHKANTOOL_PACKET_RECEIVER_HPP
#define ASHKANTOOL_PACKET_RECEIVER_HPP
#include <iostream>
#include "MacAddress.h"
#include "IpAddress.h"
#include "Logger.h"
#include "PcapPlusPlusVersion.h"
#include "PcapLiveDeviceList.h"
#include "PcapLiveDevice.h"
#include "NetworkUtils.h"
#include <getopt.h>
#include "SystemUtils.h"
#include "EthLayer.h"
#include "IPLayer.h"
#include "Packet.h"
#include <map>
#include "../../../utils/logger.hpp"
#include "VlanLayer.h"
#include "PayloadLayer.h"
#include "IpAddress.h"
#include "../task/task.hpp"
#include <netinet/in.h>
#include <EthDot3Layer.h>
#include <LLCLayer.h>


namespace ashk {

    struct ArpPoisoningDetectionCookie {
        std::map<pcpp::IPv4Address, std::vector<pcpp::MacAddress>> ip_mac_map;
    };
    struct VlanHoppingCookie {
        int inner_id;
        int outer_id;
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
    class PacketReceiver {
    public:
        static void onPacketArrivesArpPoisoningDetection(pcpp::RawPacket *raw_packet, pcpp::PcapLiveDevice *dev, void *cookie);
        static void onPacketArrivesVlanHopping(pcpp::RawPacket *raw_packet, pcpp::PcapLiveDevice *dev, void *cookie);
        static void onPacketArrivesMITMForwarding(pcpp::RawPacket *raw_packet, pcpp::PcapLiveDevice *dev, void *cookie);
        static void onPacketArrivesDTPDomainExtraction(pcpp::RawPacket *raw_packet, pcpp::PcapLiveDevice *dev, void *cookie);
    };


}

#endif //ASHKANTOOL_PACKET_RECEIVER_HPP
