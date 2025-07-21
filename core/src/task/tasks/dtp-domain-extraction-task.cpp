//
// Created by dev on 7/10/25.
//

#include "dtp-domain-extraction-task.hpp"

ashk::tasks::DtpDomainExtraction::DtpDomainExtraction(pcpp::PcapLiveDevice *dev, pcpp::IPv4Address iface_ip,char buffer[32],
                                                      int last_task_id):dev_(dev),iface_ip(iface_ip),buffer(buffer),last_task_id(last_task_id) {

}

void ashk::tasks::DtpDomainExtraction::exec() {
    logger.log("starting dtp domain extraction . . .\n");
    dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(iface_ip);
    if (dev_ == nullptr) {
        logger.log("couldn't find device\n");
        return;
    }
    if (!dev_->open()) {
        logger.log("couldn't open device");
        return;
    }

    DTPDomainExtractionCookie cookie;
    cookie.buffer=buffer;
    cookie.task= this;
    if (!capture_wrapper.start_capture(dev_, PacketReceiver::onPacketArrivesDTPDomainExtraction, &cookie,
                                       last_task_id)) {
        return;
    }
    while (is_running()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    capture_wrapper.stop_capture(dev_);
    logger.log("dtp domain extraction finished.\n");
}

std::string ashk::tasks::DtpDomainExtraction::get_data(ashk::tasks_data_id data_id) {
    if(!extractable_data.count(data_id))
        return "";
    switch (data_id) {
        default:
            return "";
    }
}


