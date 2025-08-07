//
// Created by dev on 7/10/25.
//

#include "../packet-receiver.hpp"

void ashk::PacketReceiver::onPacketArrivesDTPDomainExtraction(pcpp::RawPacket *raw_packet, pcpp::PcapLiveDevice *dev,
                                                              void *cookie) {

    auto *data = static_cast<DTPDomainExtractionCookie *>(cookie);
    if(!data->task->is_running())
        return;
    pcpp::Packet originalPacket(raw_packet);

    auto *ethLayer = originalPacket.getLayerOfType<pcpp::EthDot3Layer>();
    if (ethLayer == nullptr) {
        return;
    }
    auto *llc_layer = originalPacket.getLayerOfType<pcpp::LLCLayer>();
    if (llc_layer == nullptr) {
        return;
    }
    const static uint8_t cisco_broad_cast[]={0x01,0x00,0x0c,0xcc,0xcc,0xcc};
    if(memcmp(cisco_broad_cast,ethLayer->getDestMac().getRawData(),6)!=0)
        return;
    if(llc_layer->getLlcHeader()->ssap!=0xaa || llc_layer->getLlcHeader()->dsap!=0xaa || llc_layer->getLlcHeader()->control!=0x03)
        return;
    auto snap_layer=llc_layer->getLayerPayload();
    auto snap_size=llc_layer->getLayerPayloadSize();
    const static uint8_t snap_dtp[]={0x00,0x00,0x0c,0x20,0x04};
    if(memcmp(snap_layer,snap_dtp,5)!=0)
        return;
    auto dtp_layer =snap_layer+5;

    uint16_t domain_length=(*(dtp_layer+3)<<8) | (*(dtp_layer+4)) - 5;
    std::string domain;
    for(int i=0;i<domain_length;i++){
        domain+=(char)*(dtp_layer+5+i);
    }
    memcpy(data->buffer,domain.c_str(),domain_length);
    utils::Logger::getInstance().log("extracted domain name: "+domain+"\n");
    data->task->end();
}