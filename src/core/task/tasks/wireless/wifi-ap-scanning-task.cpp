//
// Created by dev on 7/22/25.
//

#include "wifi-ap-scanning-task.hpp"

#include <utility>
#include "PcapFileDevice.h"
#include "Packet.h"

ashk::tasks::WifiApScanningTask::WifiApScanningTask(pcpp::PcapLiveDevice *dev,
                                                    std::string iface_name_or_ip,
                                                    std::vector<WifiAp> &ap_list,
                                                    int last_task_id) :
    dev_(dev),
    iface_name_or_ip_(std::move(iface_name_or_ip)),
    Task(last_task_id), ap_list_(&ap_list) {

}

std::string ashk::tasks::WifiApScanningTask::GetData(tasks_data_id data_id) {
  return std::string();
}

void ashk::tasks::WifiApScanningTask::Exec_() {
  logger_.Log("starting network ap scan . . .\n");
  dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIpOrName(iface_name_or_ip_);
  if (dev_ == nullptr) {
    logger_.Log("couldn't find device\n");
    return;
  }
  if (!dev_->open()) {
    logger_.Log("couldn't open device");
    return;
  }
  WifiApScanningCookie cookie{
      ap_list_
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





  if (!capture_wrapper_.StartCapture(dev_, PacketReceiver::onPacketArrivesWifiApScanning, &cookie, last_task_id_))
    return;
  while (IsRunning()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  capture_wrapper_.StopCapture(dev_);
  End();
  logger_.Log("wifi scanning finished\n");
}
