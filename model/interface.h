//
// Created by dev on 6/4/25.
//

#ifndef ASHKANTOOL_INTERFACE_H
#define ASHKANTOOL_INTERFACE_H

#include "include/net_core.h"
#include <string>
class ModelInterface {
public:
    ModelInterface();
    std::string arp(std::string ip);
    std::string get_interface_ip();
private:
    Net_core core_;
};


#endif //ASHKANTOOL_INTERFACE_H
