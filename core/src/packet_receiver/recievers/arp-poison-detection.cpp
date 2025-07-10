//
// Created by dev on 7/10/25.
//


#include "../packet-receiver.hpp"

void ashk::PacketReceiver::onPacketArrivesArpPoisoningDetection(pcpp::RawPacket *raw_packet, pcpp::PcapLiveDevice *dev,
                                                                void *cookie)  {
    auto *data = static_cast<ArpPoisoningDetectionCookie *>(cookie);
    pcpp::Packet packet(raw_packet);

    if (!packet.isPacketOfType(pcpp::Ethernet) ||
        !packet.isPacketOfType(pcpp::ARP))
        return;

    auto *eth_layer = packet.getLayerOfType<pcpp::EthLayer>();
    auto *ip_layer = packet.getLayerOfType<pcpp::IPLayer>();
    auto *arp_layer = packet.getLayerOfType<pcpp::ArpLayer>();

    if(arp_layer->isRequest()){
        return;
    }
    std::cout<<arp_layer->toString()<<std::endl;
    pcpp::IPv4Address arp_sender_ip = arp_layer->getSenderIpAddr();
    pcpp::MacAddress arp_sender_mac = arp_layer->getSenderMacAddress();
//    utils::Logger::getInstance().log("got arp reply from : "+arp_sender_ip.toString()+"\n");
    if (data->ip_mac_map.count(arp_sender_ip)) {
        if (!data->ip_mac_map[arp_sender_ip].empty() &&
            arp_sender_mac != data->ip_mac_map[arp_sender_ip][0]) {
            utils::Logger::getInstance().log(
                    "found 2 or more mac addresses for " + arp_sender_ip.toString() + "\n.");
        } else {
            data->ip_mac_map[arp_sender_ip].push_back(arp_layer->getSenderMacAddress());
        }

    } else {
        data->ip_mac_map[arp_sender_ip]=std::vector<pcpp::MacAddress>{arp_layer->getSenderMacAddress()};
    }
}