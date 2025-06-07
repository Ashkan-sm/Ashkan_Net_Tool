//
// Created by dev on 6/4/25.
//

#ifndef ASHKANTOOL_INTERFACE_HPP
#define ASHKANTOOL_INTERFACE_HPP

#include "include/net-core.hpp"
#include <string>
#include "include/logger.hpp"
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

    void add_logger_method(std::function<void(const std::string &)> method);
    std::vector<int> get_live_threads();
    void kill_thread(int id);

private:
    Net_core core_;
    Logger &logger_ = Logger::getInstance();


};

}
#endif //ASHKANTOOL_INTERFACE_HPP
