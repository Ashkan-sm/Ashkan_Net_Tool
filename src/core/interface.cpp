//
// Created by dev on 6/4/25.
//

#include "interface.hpp"

#include <utility>


std::string ashk::ModelInterface::get_interface_ip() {
    return core_.interface_ip().toString();
}
std::vector<pcpp::PcapLiveDevice *> ashk::ModelInterface::get_interfaces() {
    return core_.discover_interfaces();
}


std::string ashk::ModelInterface::arp(const std::string &ip) {
    return core_.arp(pcpp::IPv4Address(ip)).toString();
}

void ashk::ModelInterface::start_arp_poison(const std::string& iface_ip, const std::string& vic_src_ip, const std::string& vic_dst_ip,
                                      const std::string& forward_to_ip) {
    pcpp::IPv4Address iface;
    pcpp::IPv4Address vic_src;
    pcpp::IPv4Address vic_dst;
    pcpp::IPv4Address forward_to;

    try {
        iface = pcpp::IPv4Address(iface_ip);
        vic_src = pcpp::IPv4Address(vic_src_ip);
        vic_dst = pcpp::IPv4Address(vic_dst_ip);
        forward_to = pcpp::IPv4Address(forward_to_ip);

    }
    catch (const std::exception &) {
        logger_.log("invalid ip inputs\n");
        return;
    }

    core_.start_arp_poisoning(iface, vic_src, vic_dst, forward_to);


}

void ashk::ModelInterface::add_logger_method(const std::function<void(const std::string &)>& method) {
    logger_.add_log_method(method);
}

std::vector<int> ashk::ModelInterface::get_running_tasks() {
    return core_.get_running_tasks();
}

void ashk::ModelInterface::end_task(int id) {
    core_.end_task(id);
}

void ashk::ModelInterface::start_arp_poison_detection(const std::string& iface_ip) {
    pcpp::IPv4Address iface;

    try {
        iface = pcpp::IPv4Address(iface_ip);

    }
    catch (const std::exception &) {
        logger_.log("invalid ip inputs\n");
        return;
    }
    core_.start_arp_poison_detection(iface_ip);

}

void ashk::ModelInterface::send_arp_req(const std::string& iface_ip_str, const std::string& ip_str) {
    pcpp::IPv4Address iface;
    pcpp::IPv4Address ip;

    try {
        iface = pcpp::IPv4Address(iface_ip_str);
        ip = pcpp::IPv4Address(ip_str);

    }
    catch (const std::exception &) {
        logger_.log("invalid ip inputs\n");
        return;
    }
    core_.send_arp_req(iface,ip);
}
void ashk::ModelInterface::start_mitm_forwarding(const std::string& iface_ip_str,const std::string& victim_ip_str, const std::string& gateway_ip_str,const std::string& victim_mac_str, const std::string& gateway_mac_str) {
    pcpp::IPv4Address iface;
    pcpp::MacAddress victim_mac;
    pcpp::MacAddress gateway_mac;
    pcpp::IPv4Address victim_ip;
    pcpp::IPv4Address gateway_ip;
    try {
        iface = pcpp::IPv4Address(iface_ip_str);
        victim_mac=pcpp::MacAddress(victim_mac_str);
        gateway_mac=pcpp::MacAddress(gateway_mac_str);
        victim_ip=pcpp::IPv4Address(victim_ip_str);
        gateway_ip=pcpp::IPv4Address(gateway_ip_str);
    }
    catch (const std::exception &) {
        logger_.log("invalid ip inputs\n");
        return;
    }
    core_.start_mitm_forwarding(iface,victim_ip,gateway_ip,victim_mac,gateway_mac);
}

void ashk::ModelInterface::start_vlan_hopping(const std::string& iface_ip_str, const std::string& outer_str, const std::string& inner_str) {
    pcpp::IPv4Address iface;
    int outer_tag=0;
    int inner_tag=0;
    try {
        iface = pcpp::IPv4Address(iface_ip_str);
        if(!outer_str.empty()) {
            outer_tag = std::stoi(outer_str);
        }
        if(!inner_str.empty()) {
            inner_tag = std::stoi(inner_str);
        }

    }
    catch (const std::exception &) {
        logger_.log("invalid inputs\n");
        return;
    }
    core_.start_vlan_hopping(iface,outer_tag,inner_tag);
}

void ashk::ModelInterface::start_dtp_negotiation(const std::string& iface_ip_str,const std::string& domain_name) {
    pcpp::IPv4Address iface;
    try {
        iface = pcpp::IPv4Address(iface_ip_str);
    }
    catch (const std::exception &) {
        logger_.log("invalid inputs\n");
        return;
    }
    core_.start_dtp_negotiation(iface,domain_name);

}

void ashk::ModelInterface::start_dtp_domain_extraction(const std::string& iface_ip_str, char *buffer) {
    pcpp::IPv4Address iface;
    try {
        iface = pcpp::IPv4Address(iface_ip_str);
    }
    catch (const std::exception &) {
        logger_.log("invalid inputs\n");
        return;
    }
    core_.start_dtp_domain_extraction(iface,buffer);
}


std::string ashk::ModelInterface::get_task_data(const std::string& task_id, tasks_data_id data_id) {
    int task_id_int=0;
    try {
        task_id_int = std::stoi(task_id);
    }catch (const std::exception &) {
        logger_.log("invalid inputs\n");
        return "";
    }
    if (!core_.tasks.count(task_id_int))
        return "";
    return core_.tasks[task_id_int]->get_data(data_id);
}

void ashk::ModelInterface::start_detecting_wifi_aps(const std::string& iface_name_str,std::vector<WifiAp> &ap_list) {

    core_.start_detecting_wifi_aps(iface_name_str,ap_list);

}

void ashk::ModelInterface::start_detecting_wifi_hosts(const std::string &iface_ip_name_str,
                                                      std::vector<std::shared_ptr<WifiHost>> &host_list) {
    core_.start_detecting_wifi_hosts(iface_ip_name_str,host_list);
}

std::string ashk::ModelInterface::get_interface_nmae() {
    return core_.interface_name();
}

void ashk::ModelInterface::start_sending_deauth_packets(const std::string &iface_ip_name_str,
                                                        WifiAp* wifi_ap,
                                                        std::vector<std::shared_ptr<WifiHost>> &host_list) {
    core_.start_sending_deauth_packets(iface_ip_name_str,wifi_ap,host_list);
}

void ashk::ModelInterface::start_password_cracking(const std::string &iface_ip_name_str, std::shared_ptr<HandShakeData> handshake_data) {
    core_.start_password_cracking(iface_ip_name_str,std::move(handshake_data));
}

void ashk::ModelInterface::start_wpa2_handshake_capturing(const std::string &iface_ip_name_str,
                                                          std::shared_ptr<HandShakeData> handshake_data) {
    core_.start_wpa2_handshake_capturing(iface_ip_name_str,std::move(handshake_data));
}


