//
// Created by dev on 7/23/25.
//

#include "wifi-host-scanning-task.hpp"

ashk::tasks::WifiHostScanningTask::WifiHostScanningTask(pcpp::PcapLiveDevice *dev,
                                                        std::string iface_name_or_ip,
                                                        std::vector<std::shared_ptr<WifiHost>> &host_list,
                                                        int last_task_id) :
    dev_(dev),
    iface_name_or_ip_(iface_name_or_ip),
    Task(last_task_id), host_list_(&host_list) {

}

std::string ashk::tasks::WifiHostScanningTask::GetData(tasks_data_id data_id) {
  return std::string();
}

void ashk::tasks::WifiHostScanningTask::Exec_() {
  logger_.Log("starting wifi host scanning . . .\n");
  dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIpOrName(iface_name_or_ip_);
  if (dev_ == nullptr) {
    logger_.Log("couldn't find device\n");
    return;
  }
  if (!dev_->open()) {
    logger_.Log("couldn't open device");
    return;
  }
  WifiHostScanningCookie cookie{
      host_list_
  };
  if (!capture_wrapper_.StartCapture(dev_, PacketReceiver::onPacketArrivesWifiHostScanning, &cookie, last_task_id_))
    return;
  while (IsRunning()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  capture_wrapper_.StopCapture(dev_);
  End();
  logger_.Log("wifi scanning finished\n");

}
