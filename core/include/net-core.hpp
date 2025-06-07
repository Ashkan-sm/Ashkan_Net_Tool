//
// Created by dev on 6/5/25.
//

#ifndef ASHKANTOOL_NET_CORE_HPP
#define ASHKANTOOL_NET_CORE_HPP

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
#include "logger.hpp"
#include <map>

#include "packet-receiver.hpp"
#include "capture-wrapper.hpp"
namespace ashk {
    class Net_core {
    public:
        friend class ModelInterface;
        Net_core();

    private:
        pcpp::MacAddress arp(pcpp::IPv4Address ip);
        void send_arp_req(pcpp::IPv4Address iface_ip,pcpp::IPv4Address ip);
        int discover_interface();

        pcpp::IPv4Address interface_ip();

        void start_arp_poisoning(pcpp::IPv4Address iface_ip, pcpp::IPv4Address vic_src_ip, pcpp::IPv4Address vic_dst_ip,
                                 pcpp::IPv4Address forward_to_ip);

        void start_arp_poison_detection(pcpp::IPv4Address iface_ip);

        void add_logger_method(const std::function<void(const std::string &)> &method);

        void add_live_thread(std::function<void(std::shared_ptr<bool>)> func);

        void kill_thread(int id);

        std::vector<int> get_live_threads();

        pcpp::PcapLiveDevice *dev_ = nullptr;
        ashk::Logger &logger_ = ashk::Logger::getInstance();
        CaptureWrapper &capture_wrapper = CaptureWrapper::getInstance();
        std::map<int, std::shared_ptr<std::thread>> live_threads;
        std::map<int, std::shared_ptr<bool>> live_thread_alive;
        int last_added_thread_id = 0;
    };
}

#endif //ASHKANTOOL_NET_CORE_HPP
