//
// Created by dev on 7/22/25.
//

#include "wifi-ap-scanning-task.hpp"
#include "PcapFileDevice.h"
#include "Packet.h"

ashk::tasks::WifiApScanningTask::WifiApScanningTask(pcpp::PcapLiveDevice *dev,
                                                    std::string iface_name_or_ip,
                                                    std::vector<WifiAp> &ap_list,
                                                    int last_task_id):
        dev_(dev),
        iface_name_or_ip(iface_name_or_ip),
        last_task_id(last_task_id),ap_list(&ap_list) {

}

std::string ashk::tasks::WifiApScanningTask::get_data(ashk::tasks_data_id data_id) {
    return std::string();
}

void ashk::tasks::WifiApScanningTask::exec() {
    logger.log("starting network ap scan . . .\n");
    dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIpOrName(iface_name_or_ip);
    if (dev_ == nullptr) {
        logger.log("couldn't find device\n");
        return;
    }
    if (!dev_->open()) {
        logger.log("couldn't open device");
        return;
    }
    WifiApScanningCookie cookie{
        ap_list
    };
//    pcpp::PcapFileReaderDevice reader("/home/dev/Downloads/wireless.pcap");
//
//    if (!reader.open()) {
//        std::cerr << "Error opening pcap file: " << "/home/dev/Downloads/wireless.pcap" << std::endl;
//        return;
//    }
//
//    pcpp::RawPacket rawPacket;
//
//    while (reader.getNextPacket(rawPacket)) {
//        PacketReceiver::onPacketArrivesWifiApScanning(&rawPacket,dev_,&cookie);
//    }
//
//    reader.close();





    if (!capture_wrapper.start_capture(dev_, PacketReceiver::onPacketArrivesWifiApScanning, &cookie, last_task_id))
        return;
    while (is_running()) {
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    capture_wrapper.stop_capture(dev_);
    end();
    logger.log("wifi scanning finished\n");
}
