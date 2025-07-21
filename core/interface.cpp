//
// Created by dev on 6/4/25.
//

#include "interface.hpp"
namespace ashk {

ModelInterface::ModelInterface() {

}

std::string ModelInterface::get_interface_ip() {
    return core_.interface_ip().toString();
}

std::string ModelInterface::arp(std::string ip) {
    return core_.arp(pcpp::IPv4Address(ip)).toString();
}

void ModelInterface::start_arp_poison(std::string iface_ip, std::string vic_src_ip, std::string vic_dst_ip,
                                      std::string forward_to_ip) {
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

void ModelInterface::add_logger_method(std::function<void(const std::string &)> method) {
    logger_.add_log_method(method);
}

std::vector<int> ModelInterface::get_running_tasks() {
    return core_.get_running_tasks();
}

void ModelInterface::end_task(int id) {
    core_.end_task(id);
}

void ModelInterface::start_arp_poison_detection(std::string iface_ip) {
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

void ModelInterface::send_arp_req(const std::string& iface_ip_str, const std::string& ip_str) {
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
    void ModelInterface::start_mitm_forwarding(const std::string& iface_ip_str,std::string victim_mac, std::string gateway_mac) {
        pcpp::IPv4Address iface;

        try {
            iface = pcpp::IPv4Address(iface_ip_str);
        }
        catch (const std::exception &) {
            logger_.log("invalid ip inputs\n");
            return;
        }
        core_.start_mitm_forwarding(iface,victim_mac,gateway_mac);
    }

    void ModelInterface::start_vlan_hopping(std::string iface_ip_str, std::string outer_str, std::string inner_str) {
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

    void ModelInterface::start_dtp_negotiation(std::string iface_ip_str,const std::string& domain_name) {
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

    void ModelInterface::start_dtp_domain_extraction(std::string iface_ip_str, char *buffer) {
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


}
