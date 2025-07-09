//
// Created by dev on 6/5/25.
//

#include "net-core.hpp"

namespace ashk {

Net_core::Net_core()=default;


int Net_core::discover_interface() {
    std::vector<pcpp::PcapLiveDevice *> deviceList = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();

    for (auto i: deviceList) {
        if (i->getIPv4Address() != pcpp::IPv4Address("0.0.0.0") &&
            i->getIPv4Address() != pcpp::IPv4Address("127.0.0.1")) {
            dev_ = i;
            return 1;
        }
    }

    return 0;
}

pcpp::IPv4Address Net_core::interface_ip() {
    discover_interface();
    return dev_->getIPv4Address();
}

void Net_core::start_arp_poisoning(pcpp::IPv4Address iface_ip, pcpp::IPv4Address vic_src_ip,
                                   pcpp::IPv4Address vic_dst_ip,
                                   pcpp::IPv4Address forward_to_ip) {

    tasks[last_added_task_id] = std::make_unique<tasks::ArpPoisoningTask>(dev_,vic_src_ip,vic_dst_ip,forward_to_ip,iface_ip);
    tasks[last_added_task_id]->start();
    last_added_task_id++;
}

void Net_core::add_logger_method(const std::function<void(const std::string &)> &method) {
    logger_.add_log_method(method);
}


void Net_core::end_task(int id) {
    tasks[id]->end();
    logger_.log("stopped task" + std::to_string(id) + " .\n");
}

std::vector<int> Net_core::get_running_tasks() {
    std::vector<int> out;
    for (const auto &i: tasks) {
        if (i.second->is_running()) {
            out.push_back(i.first);
        }
    }
    return out;
}

void Net_core::start_arp_poison_detection(pcpp::IPv4Address iface_ip) {
    tasks[last_added_task_id]=std::make_unique<tasks::ArpPoisonDetectionTask>(iface_ip,last_added_task_id);
    tasks[last_added_task_id]->start();
    last_added_task_id++;

}

void Net_core::send_arp_req(pcpp::IPv4Address iface_ip, pcpp::IPv4Address ip) {
    dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(iface_ip);
    if (dev_ == nullptr) {
        logger_.log("couldn't find device\n");
        return;
    }
    if (!dev_->open()) {
        logger_.log("couldn't open device");
        return;
    }
    pcpp::Packet arpRequest(100);

    pcpp::EthLayer ethLayer(dev_->getMacAddress(), pcpp::MacAddress::Broadcast);
    pcpp::ArpLayer arpLayer(pcpp::ArpRequest(dev_->getMacAddress(), iface_ip, ip));

    if (!arpRequest.addLayer(&ethLayer))
    {
        logger_.log("Couldn't build Eth layer for ARP request");
        return;
    }

    if (!arpRequest.addLayer(&arpLayer))
    {
        logger_.log("Couldn't build ARP layer for ARP request\n");
        return;
    }
    arpRequest.computeCalculateFields();
    if(!dev_->sendPacket(&arpRequest)) {
        logger_.log("Unable to send Packet\n");
        return;
    }
    logger_.log("Sent arp request\n");
}

pcpp::MacAddress Net_core::arp(pcpp::IPv4Address ip) {
    return NetUtils::arp(ip,dev_);
}


    void Net_core::start_mitm_forwarding(pcpp::IPv4Address iface_ip, pcpp::IPv4Address victim, pcpp::IPv4Address gateway) {
        tasks[last_added_task_id]=std::make_unique<tasks::MITMPacketForwarding>(iface_ip,victim,gateway,last_added_task_id);
        tasks[last_added_task_id]->start();
        last_added_task_id++;
    }

    void Net_core::start_vlan_hopping(pcpp::IPv4Address iface_ip, int outer_id, int inner_id) {
        tasks[last_added_task_id]=std::make_unique<tasks::VlanHoppingTask>(dev_,iface_ip,outer_id,inner_id,last_added_task_id);
        tasks[last_added_task_id]->start();
        last_added_task_id++;
    }

    void Net_core::start_dtp_negotiation(pcpp::IPv4Address iface_ip, const std::string &domain_name) {
        tasks[last_added_task_id]=std::make_unique<tasks::DTPNegotiation>(dev_,iface_ip,domain_name,last_added_task_id);
        tasks[last_added_task_id]->start();
        last_added_task_id++;
    }


}