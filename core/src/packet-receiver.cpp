#include "packet-receiver.hpp"

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

void ashk::PacketReceiver::onPacketArrivesVlanHopping(pcpp::RawPacket *rawPacket, pcpp::PcapLiveDevice *dev, void *cookie) {
    auto *data = static_cast<VlanHoppingCookie *>(cookie);

    // Parse the original packet
    pcpp::Packet originalPacket(rawPacket);

    auto *ethLayer = originalPacket.getLayerOfType<pcpp::EthLayer>();
    if (ethLayer == nullptr) {
        std::cerr << "No Ethernet layer found!" << std::endl;
        return;
    }

    pcpp::MacAddress srcMac = ethLayer->getSourceMac();
    pcpp::MacAddress dstMac = ethLayer->getDestMac();
    if(srcMac!=dev->getMacAddress()){
        return;
    }
    auto *vlan_layer = originalPacket.getLayerOfType<pcpp::VlanLayer>();
    if (vlan_layer != nullptr) {
        return;
    }
    pcpp::Packet new_packet(rawPacket->getRawDataLen()+100);
    pcpp::EthLayer new_ethlayer(*ethLayer);
    new_packet.addLayer(&new_ethlayer);
    pcpp::VlanLayer vlanlayer(data->vlan_id, false,1,PCPP_ETHERTYPE_IP);
    new_packet.addLayer(&vlanlayer);


    for(pcpp::Layer *layer=ethLayer->getNextLayer();layer!= nullptr;layer=layer->getNextLayer()){
        uint8_t lArr[layer->getDataLen()];
        layer->copyData(lArr);
        auto *new_layer=new pcpp::PayloadLayer(lArr, sizeof(lArr));
        new_packet.addLayer(new_layer);
    }
    new_packet.computeCalculateFields();
    dev->sendPacket(&new_packet);
}

