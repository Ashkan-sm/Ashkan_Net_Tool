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
    MITMForwardingCookie cookie;

    cookie.gateway_ip=gateway_ip;
    cookie.victim_ip=victim_ip;
    cookie.victim_mac=victim_mac;
    cookie.gateway_mac=gateway_mac;

    if (!capture_wrapper.start_capture(dev_, PacketReceiver::onPacketArrivesMITMForwarding, &cookie,last_task_id))
        return;
    while (is_running()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    capture_wrapper.stop_capture(dev_);
    end();
    logger.log("mitm forwarding stopped.\n");
}
ashk::tasks::MITMPacketForwarding::MITMPacketForwarding(pcpp::IPv4Address iface_ip, pcpp::IPv4Address victim_ip,
                                                        pcpp::IPv4Address gateway_ip, pcpp::MacAddress victim_mac,
                                                        pcpp::MacAddress gateway_mac, int last_task_id) : iface_ip(iface_ip),victim_mac(victim_mac),
                                                        gateway_mac(gateway_mac),victim_ip(victim_ip),gateway_ip(gateway_ip),Task(last_task_id) {

}
std::string ashk::tasks::MITMPacketForwarding::get_data(tasks_data_id data_id) {
    if(!extractable_data.count(data_id))
        return "";
    switch (data_id) {
        default:
            return "";
    }
}

