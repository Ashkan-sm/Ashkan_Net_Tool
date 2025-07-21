//
// Created by dev on 6/9/25.
//

#include "arp-poison-detection-task.hpp"

void ashk::tasks::ArpPoisonDetectionTask::exec() {
    logger.log("starting arp poison detection . . .\n");
    dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(iface_ip);
    if (dev_ == nullptr) {
        logger.log("couldn't find device\n");
        return;
    }
    if (!dev_->open()) {
        logger.log("couldn't open device");
        return;
    }

    ArpPoisoningDetectionCookie cookie;
    if (!capture_wrapper.start_capture(dev_, PacketReceiver::onPacketArrivesArpPoisoningDetection, &cookie,
                                       last_task_id))
        return;
    while (is_running()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    capture_wrapper.stop_capture(dev_);
    logger.log("ArpPoisonDetection task finished.\n");
}

ashk::tasks::ArpPoisonDetectionTask::ArpPoisonDetectionTask(pcpp::IPv4Address iface_ip,int last_task_id):iface_ip(iface_ip),last_task_id(last_task_id) {

}

std::string ashk::tasks::ArpPoisonDetectionTask::get_data(tasks_data_id data_id) {
    if(!extractable_data.count(data_id))
        return "";
    switch (data_id) {
        default:
            return "";
    }
}
