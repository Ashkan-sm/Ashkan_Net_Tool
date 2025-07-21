//
// Created by dev on 7/9/25.
//

#include "dtp-negotiation.hpp"

ashk::tasks::DTPNegotiation::DTPNegotiation(pcpp::PcapLiveDevice *dev, pcpp::IPv4Address iface_ip,std::string domain_name, int last_task_id):dev_(dev),iface_ip(iface_ip),
domain_name(domain_name){

}

void ashk::tasks::DTPNegotiation::exec() {
    logger.log("start dtp negotiation . . .\n");
    dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(iface_ip);
    if (dev_ == nullptr) {
        logger.log("couldn't find device\n");
        return;
    }
    if (!dev_->open()) {
        logger.log("couldn't open device");
        return;
    }
    ;
    //create dtp trunk desirable packet
    uint16_t domain_lenght= htons(domain_name.size()+5);
    uint8_t base_dtp_layer[]={0x01, //version
                        0x00,0x01, //domain type
                        0x00,0x00, //domain length
                        0x00,//domain name
                        0x00,0x02, //trunk status
                        0x00,0x05,0x83, //trunk length , value
                        0x00,0x03,0x00,0x05,0x40, //trunk type , length,value
                        0x00,0x04,0x00,0x0a,//sender id type,length
                        0,0,0,0,0,0 //id
    };
    memcpy(base_dtp_layer+3,&domain_lenght,2);
    uint8_t dtp_layer[sizeof(base_dtp_layer)+domain_name.size()];
    memcpy(dtp_layer,base_dtp_layer,5);
    memcpy(dtp_layer+5,domain_name.c_str(),domain_name.size());
    memcpy(dtp_layer+5+domain_name.size(),base_dtp_layer+5,sizeof(base_dtp_layer)-5);

    dev_->getMacAddress().copyTo(dtp_layer+ sizeof(dtp_layer)-6);

    uint8_t LLC_layer[]={
            0xaa,0xaa,0x03,0x00,0x00,0x0c,0x20,0x04 //llc for dtp
    };
    uint8_t ieee_eth_layer[14]={0x01,0x00,0x0c,0xcc,0xcc,0xcc };//dest mac
    dev_->getMacAddress().copyTo(ieee_eth_layer+6);
    uint16_t eth_payload_size=htons(sizeof(LLC_layer)+sizeof(dtp_layer));
    memcpy(ieee_eth_layer+12,&eth_payload_size,2);


    const size_t totalLen = sizeof(ieee_eth_layer) + sizeof(LLC_layer) + sizeof(dtp_layer);
    uint8_t* fullPacket = new uint8_t[totalLen];
    size_t offset = 0;

    memcpy(fullPacket + offset, ieee_eth_layer, sizeof(ieee_eth_layer));
    offset += sizeof(ieee_eth_layer);

    memcpy(fullPacket + offset, LLC_layer, sizeof(LLC_layer));
    offset += sizeof(LLC_layer);

    memcpy(fullPacket + offset, dtp_layer, sizeof(dtp_layer));

    // --- Create RawPacket ---
    timeval ts = {0, 0};
    pcpp::RawPacket raw(fullPacket, totalLen, ts, false);
    pcpp::Packet new_packet(&raw);
    new_packet.computeCalculateFields();

    while (is_running()) {
        dev_->sendPacket(&new_packet);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    logger.log("dtp negotiation finished.\n");
}
std::string ashk::tasks::DTPNegotiation::get_data(tasks_data_id data_id) {
    if(!extractable_data.count(data_id))
        return "";
    switch (data_id) {
        default:
            return "";
    }
}
