//
// Created by dev on 6/5/25.
//

#include "../include/net_core.h"

Net_core::Net_core() {

}

pcpp::MacAddress Net_core::arp(pcpp::IPv4Address ip) {
    double arpResponseTimeMS;
    double arpTimeOut=2;
    return pcpp::NetworkUtils::getInstance().getMacAddress(ip, dev_, arpResponseTimeMS,
                                                           dev_->getMacAddress(), dev_->getIPv4Address(), arpTimeOut);
}

int Net_core::discover_interface() {
    std::vector<pcpp::PcapLiveDevice*> deviceList=pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();

    for (auto i: deviceList) {
        if (i->getIPv4Address() != pcpp::IPv4Address("0.0.0.0") &&
            i->getIPv4Address() != pcpp::IPv4Address("127.0.0.1")) {
            dev_=i;
            return 1;
        }
    }

    return 0;
}

pcpp::IPv4Address Net_core::interface_ip() {
    if(dev_== nullptr){
        discover_interface();
    }
    return dev_->getIPv4Address();
}
