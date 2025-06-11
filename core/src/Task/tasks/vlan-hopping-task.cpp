//
// Created by dev on 6/10/25.
//

#include "vlan-hopping-task.hpp"


ashk::tasks::VlanHoppingTask::VlanHoppingTask(pcpp::PcapLiveDevice *dev,
                                              pcpp::IPv4Address iface_ip,
                                              int vlan_id,
                                              int last_task_id):
                                              dev_(dev),
                                              iface_ip(iface_ip),
                                              vlan_id(vlan_id),
                                              last_task_id(last_task_id){


}

void ashk::tasks::VlanHoppingTask::exec() {
    logger.log("starting vlan hopping . . .\n");
    dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(iface_ip);
    if (dev_ == nullptr) {
        logger.log("couldn't find device\n");
        return;
    }
    if (!dev_->open()) {
        logger.log("couldn't open device");
        return;
    }

    VlanHoppingCookie cookie;
    cookie.vlan_id=vlan_id;
    if (!capture_wrapper.start_capture(dev_, PacketReceiver::onPacketArrivesVlanHopping, &cookie,last_task_id))
        return;
    while (m.test()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    capture_wrapper.stop_capture(dev_);
    logger.log("vlan hopping task finished.\n");
}
