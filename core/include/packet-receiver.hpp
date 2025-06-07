//
// Created by dev on 6/5/25.
//

#ifndef ASHKANTOOL_PACKET_RECEIVER_HPP
#define ASHKANTOOL_PACKET_RECEIVER_HPP
#include <iostream>
#include <MacAddress.h>
#include <IpAddress.h>
#include <Logger.h>
#include <PcapPlusPlusVersion.h>
#include <PcapLiveDeviceList.h>
#include <PcapLiveDevice.h>
#include <NetworkUtils.h>
#include <getopt.h>
#include <SystemUtils.h>
#include <EthLayer.h>
#include <IPLayer.h>
#include <Packet.h>
#include <map>
#include "logger.hpp"

namespace ashk {

    struct ArpPoisoningDetectionCookie {
        std::map<pcpp::IPv4Address, std::vector<pcpp::MacAddress>> ip_mac_map;
    };

    class PacketReceiver {
    public:
        static void
        onPacketArrivesArpPoisoningDetection(pcpp::RawPacket *raw_packet, pcpp::PcapLiveDevice *dev, void *cookie) {
            auto *data = static_cast<ArpPoisoningDetectionCookie *>(cookie);
            pcpp::Packet packet(raw_packet);

            if (!packet.isPacketOfType(pcpp::IPv4) || !packet.isPacketOfType(pcpp::Ethernet) ||
                !packet.isPacketOfType(pcpp::ARP))
                return;
            std::cout<<"yo"<<std::endl;
            auto *eth_layer = packet.getLayerOfType<pcpp::EthLayer>();
            auto *ip_layer = packet.getLayerOfType<pcpp::IPLayer>();
            auto *arp_layer = packet.getLayerOfType<pcpp::ArpLayer>();
            if(arp_layer->isRequest()){
                return;
            }
            std::cout<<arp_layer->toString()<<std::endl;
            pcpp::IPv4Address arp_sender_ip = arp_layer->getSenderIpAddr();
            pcpp::MacAddress arp_sender_mac = arp_layer->getSenderMacAddress();
            if (data->ip_mac_map.count(arp_sender_ip)) {
                if (data->ip_mac_map[arp_sender_ip].empty() &&
                    arp_sender_mac != data->ip_mac_map[arp_sender_ip][0]) {
                    ashk::Logger::getInstance().log(
                            "found 2 or more mac addresses for " + arp_sender_ip.toString() + "\n.");
                } else {
                    data->ip_mac_map[arp_sender_ip].push_back(arp_layer->getSenderMacAddress());
                }

            } else {
                data->ip_mac_map[arp_sender_ip]=std::vector<pcpp::MacAddress>{arp_layer->getSenderMacAddress()};
            }
        }

    };


}

#endif //ASHKANTOOL_PACKET_RECEIVER_HPP
