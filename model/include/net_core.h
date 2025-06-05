//
// Created by dev on 6/5/25.
//

#ifndef ASHKANTOOL_NET_CORE_H
#define ASHKANTOOL_NET_CORE_H

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

class Net_core {
public:
    Net_core();
    pcpp::MacAddress arp(pcpp::IPv4Address ip);
    int discover_interface();
    pcpp::IPv4Address interface_ip();

private:
    pcpp::PcapLiveDevice* dev_ = nullptr;
};


#endif //ASHKANTOOL_NET_CORE_H
