//
// Created by dev on 7/23/25.
//

#include "wifi-host-scanning-task.hpp"

ashk::tasks::WifiHostScanningTask::WifiHostScanningTask(pcpp::PcapLiveDevice *dev,
                                                        std::string iface_name_or_ip,
                                                        std::vector<std::shared_ptr<WifiHost>> &host_list,
                                                        int last_task_id) :
    dev_(dev),
    iface_name_or_ip(iface_name_or_ip),
    Task(last_task_id), host_list(&host_list) {

}

std::string ashk::tasks::WifiHostScanningTask::get_data(ashk::tasks_data_id data_id) {
  return std::string();
}

void ashk::tasks::WifiHostScanningTask::exec() {
  logger.log("starting wifi host scanning . . .\n");
  dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIpOrName(iface_name_or_ip);
  if (dev_ == nullptr) {
    logger.log("couldn't find device\n");
    return;
  }
  if (!dev_->open()) {
    logger.log("couldn't open device");
    return;
  }
  WifiHostScanningCookie cookie{
      host_list
  };
  if (!capture_wrapper.start_capture(dev_, PacketReceiver::onPacketArrivesWifiHostScanning, &cookie, last_task_id))
    return;
  while (is_running()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  capture_wrapper.stop_capture(dev_);
  end();
  logger.log("wifi scanning finished\n");

}
