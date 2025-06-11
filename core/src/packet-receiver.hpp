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
#include "../../utils/logger.hpp"
#include "VlanLayer.h"
#include "PayloadLayer.h"
namespace ashk {

    struct ArpPoisoningDetectionCookie {
        std::map<pcpp::IPv4Address, std::vector<pcpp::MacAddress>> ip_mac_map;
    };
    struct VlanHoppingCookie {
        int vlan_id;
    };
    class PacketReceiver {
    public:
        static void onPacketArrivesArpPoisoningDetection(pcpp::RawPacket *raw_packet, pcpp::PcapLiveDevice *dev, void *cookie);
        static void onPacketArrivesVlanHopping(pcpp::RawPacket *raw_packet, pcpp::PcapLiveDevice *dev, void *cookie);
    };


}

#endif //ASHKANTOOL_PACKET_RECEIVER_HPP
