//
// Created by dev on 6/4/25.
//

#include "interface.h"

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

    try
    {
        iface = pcpp::IPv4Address(iface_ip);
        vic_src = pcpp::IPv4Address(vic_src_ip);
        vic_dst = pcpp::IPv4Address(vic_dst_ip);
        forward_to = pcpp::IPv4Address(forward_to_ip);

    }
    catch (const std::exception&)
    {
        logger_.log("invalid ip inputs\n");
        return;
    }

    core_.start_arp_poisoning(iface,vic_src,vic_dst,forward_to);


}

void ModelInterface::add_logger_method(std::function<void(const std::string &)> method) {
    logger_.add_log_method(method);
}

std::vector<int> ModelInterface::get_live_threads() {
    return core_.get_live_threads();
}

void ModelInterface::kill_thread(int id) {
    core_.kill_thread(id);
}

void ModelInterface::start_arp_poison_detection(std::string iface_ip) {
    pcpp::IPv4Address iface;

    try
    {
        iface = pcpp::IPv4Address(iface_ip);

    }
    catch (const std::exception&)
    {
        logger_.log("invalid ip inputs\n");
        return;
    }
    core_.start_arp_poison_detecion(iface_ip);

}


