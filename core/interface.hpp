//
// Created by dev on 6/4/25.
//

#ifndef ASHKANTOOL_INTERFACE_HPP
#define ASHKANTOOL_INTERFACE_HPP

#include "src/net-core.hpp"
#include <string>
#include "../utils/logger.hpp"
#include "wifi-ap.hpp"
namespace ashk {

class ModelInterface {
public:
    ModelInterface()=default;

    std::string arp(const std::string &ip);
    void send_arp_req(const std::string &iface_ip_str, const std::string &ip_str);

    std::string get_interface_ip();

    void start_arp_poison(const std::string& iface_ip, const std::string& vic_src_ip, const std::string& vic_dst_ip,
                          const std::string& forward_to_ip);
    void start_arp_poison_detection(const std::string& iface_ip);
    void start_vlan_hopping(const std::string& iface_ip_str,const std::string& outer_str,const std::string& inner_str);
    void start_dtp_negotiation(const std::string& iface_ip_str,const std::string &domain_name);
    void start_dtp_domain_extraction(const std::string& iface_ip_str,char buffer[32]);
    void start_mitm_forwarding(const std::string& iface_ip_str,const std::string& victim_ip_str, const std::string& gateway_ip_str,const std::string& victim_mac_str, const std::string& gateway_mac_str);
    void start_detecting_networks(const std::string& iface_ip_str,std::vector<WifiAp> &ap_list);
    void add_logger_method(const std::function<void(const std::string &)>& method);
    std::vector<int> get_running_tasks();
    void end_task(int id);

    std::string get_task_data(const std::string& task_id,tasks_data_id data_id);


private:
    Net_core core_;
    utils::Logger &logger_ = utils::Logger::getInstance();


};

}
#endif //ASHKANTOOL_INTERFACE_HPP
