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
#include <EthLayer.h>
#include <Packet.h>
#include "logger.h"
#include <map>

class Net_core {
public:
    Net_core();
    pcpp::MacAddress arp(pcpp::IPv4Address ip);
    int discover_interface();
    pcpp::IPv4Address interface_ip();
    void start_arp_poisoning(pcpp::IPv4Address iface_ip,pcpp::IPv4Address vic_src_ip ,pcpp::IPv4Address vic_dst_ip,pcpp::IPv4Address forward_to_ip);
    void add_logger_method(std::function<void(const std::string &)> method);
    void add_live_thread(std::function<void(std::shared_ptr<bool>)> func);
    void kill_thread(int id);
    std::vector<int> get_live_threads();

private:
    pcpp::PcapLiveDevice* dev_ = nullptr;
    Logger &logger_=Logger::getInstance();
    std::map<int,std::shared_ptr<std::thread>> live_threads;
    std::map<int,std::shared_ptr<bool>> live_thread_alive;
    int last_added_thread_id=0;
};


#endif //ASHKANTOOL_NET_CORE_H
