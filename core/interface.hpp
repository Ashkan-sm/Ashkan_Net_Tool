//
// Created by dev on 6/4/25.
//

#ifndef ASHKANTOOL_INTERFACE_HPP
#define ASHKANTOOL_INTERFACE_HPP

#include "src/net-core.hpp"
#include <string>
#include "../utils/logger.hpp"
namespace ashk {

class ModelInterface {
public:
    ModelInterface();

    std::string arp(std::string ip);
    void send_arp_req(const std::string &iface_ip_str, const std::string &ip_str);

    std::string get_interface_ip();

    void start_arp_poison(std::string iface_ip, std::string vic_src_ip, std::string vic_dst_ip,
                          std::string forward_to_ip);
    void start_arp_poison_detection(std::string iface_ip);
    void start_vlan_hopping(std::string iface_ip_str,std::string outer_str,std::string inner_str);
    void start_dtp_negotiation(std::string iface_ip_str,const std::string &domain_name);
    void start_dtp_domain_extraction(std::string iface_ip_str,char buffer[32]);
    void start_mitm_forwarding(const std::string& iface_ip_str,std::string victim_ip,std::string gateway_ip);

    void add_logger_method(std::function<void(const std::string &)> method);
    std::vector<int> get_running_tasks();
    void end_task(int id);

private:
    Net_core core_;
    utils::Logger &logger_ = utils::Logger::getInstance();


};

}
#endif //ASHKANTOOL_INTERFACE_HPP
