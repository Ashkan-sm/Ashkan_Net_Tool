//
// Created by dev on 6/5/25.
//

#ifndef ASHKANTOOL_NET_CORE_HPP
#define ASHKANTOOL_NET_CORE_HPP

#include <map>

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

#include "utils/logger.hpp"
#include "utils/net-utils.hpp"

#include "core/task/task.hpp"
#include "core/task/tasks/arp/arp-poisoning-task.hpp"
#include "core/task/tasks/arp/arp-poison-detection-task.hpp"
#include "core/task/tasks/vlan/vlan-hopping-task.hpp"
#include "core/task/tasks/dtp/dtp-negotiation.hpp"
#include "core/task/tasks/man-in-the-middle/mitm-packet-forwarding.hpp"
#include "core/task/tasks/dtp/dtp-domain-extraction-task.hpp"
#include "core/task/tasks/wireless/wifi-ap-scanning-task.hpp"
#include "core/task/tasks/wireless/wifi-host-scanning-task.hpp"
#include "core/task/tasks/wireless/deauth-packet-sending.hpp"
#include "core/task/tasks/wireless/wpa-2-hand-shake-capture-task.hpp"
#include "core/task/tasks/wireless/wifi-password-cracking-task.hpp"

#include "core/data-holders/wifi.hpp"
#include "core/packet-receiver/packet-receiver.hpp"
#include "core/capture-wrapper.hpp"

namespace ashk {
    class Net_core {
    public:
        friend class ModelInterface;
        Net_core();

    private:
        pcpp::MacAddress arp(pcpp::IPv4Address ip);
        void send_arp_req(pcpp::IPv4Address iface_ip,pcpp::IPv4Address ip);
        int discover_interface();
        std::vector<pcpp::PcapLiveDevice *> discover_interfaces();

        pcpp::IPv4Address interface_ip();
        std::string interface_name();

        void start_arp_poisoning(pcpp::IPv4Address iface_ip, pcpp::IPv4Address vic_src_ip, pcpp::IPv4Address vic_dst_ip,
                                 pcpp::IPv4Address forward_to_ip);
        void start_arp_poison_detection(pcpp::IPv4Address iface_ip);
        void start_mitm_forwarding(pcpp::IPv4Address iface_ip,  pcpp::IPv4Address victim_ip, pcpp::IPv4Address gateway_ip,pcpp::MacAddress victim_mac, pcpp::MacAddress gateway_mac) ;
        void start_vlan_hopping(pcpp::IPv4Address iface_ip,int outer_id,int inner_id);
        void start_dtp_negotiation(pcpp::IPv4Address iface_ip,const std::string& domain_name);
        void start_dtp_domain_extraction(pcpp::IPv4Address iface_ip,char *buffer);
        void start_detecting_wifi_aps(std::string iface_name_or_ip,std::vector<WifiAp> &ap_list);
        void start_detecting_wifi_hosts(const std::string& iface_ip_name_str, std::vector<std::shared_ptr<WifiHost>>&host_list);
        void start_sending_deauth_packets(const std::string& iface_ip_name_str,WifiAp* wifi_ap, std::vector<std::shared_ptr<WifiHost>>&host_list);
        void start_password_cracking(const std::string& iface_ip_name_str,std::shared_ptr<HandShakeData> handshake_data);
        void start_wpa2_handshake_capturing(const std::string& iface_ip_name_str,std::shared_ptr<HandShakeData> handshake_data);

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
