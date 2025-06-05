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
