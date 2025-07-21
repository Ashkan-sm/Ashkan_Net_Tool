//
// Created by dev on 6/5/25.
//

#ifndef ASHKANTOOL_NET_CORE_HPP
#define ASHKANTOOL_NET_CORE_HPP

#include <iostream>
#include "MacAddress.h"
#include "IpAddress.h"
#include "Logger.h"
#include "PcapPlusPlusVersion.h"
#include "PcapLiveDeviceList.h"
#include "PcapLiveDevice.h"
#include "NetworkUtils.h"
#include <getopt.h>
#include "SystemUtils.h"
#include "EthLayer.h"
#include "Packet.h"
#include "../../utils/logger.hpp"
#include "../../utils/net-utils.hpp"
#include "task/task.hpp"
#include "task/tasks/arp-poisoning-task.hpp"
#include "task/tasks/arp-poison-detection-task.hpp"
#include "task/tasks/vlan-hopping-task.hpp"
#include "task/tasks/dtp-negotiation.hpp"
#include "task/tasks/mitm-packet-forwarding.hpp"
#include "task/tasks/dtp-domain-extraction-task.hpp"

#include <map>

#include "packet_receiver/packet-receiver.hpp"
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
        void start_mitm_forwarding(pcpp::IPv4Address iface_ip,  pcpp::IPv4Address victim_ip, pcpp::IPv4Address gateway_ip,pcpp::MacAddress victim_mac, pcpp::MacAddress gateway_mac) ;
        void start_vlan_hopping(pcpp::IPv4Address iface_ip,int outer_id,int inner_id);
        void start_dtp_negotiation(pcpp::IPv4Address iface_ip,const std::string& domain_name);
        void start_dtp_domain_extraction(pcpp::IPv4Address iface_ip,char *buffer);

        void add_logger_method(const std::function<void(const std::string &)> &method);
        void end_task(int id);

        std::vector<int> get_running_tasks();

        pcpp::PcapLiveDevice *dev_ = nullptr;
        utils::Logger &logger_ = utils::Logger::getInstance();
        CaptureWrapper &capture_wrapper = CaptureWrapper::getInstance();
        std::map<int, std::shared_ptr<Task>> tasks;
        int last_added_task_id = 0;
    };
}

#endif //ASHKANTOOL_NET_CORE_HPP
