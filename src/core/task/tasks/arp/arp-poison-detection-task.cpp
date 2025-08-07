//
// Created by dev on 6/9/25.
//

#include "arp-poison-detection-task.hpp"

void ashk::tasks::ArpPoisonDetectionTask::Exec_() {
  logger_.Log("starting arp poison detection . . .\n");
  dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(iface_ip_);
  if (dev_ == nullptr) {
    logger_.Log("couldn't find device\n");
    return;
  }
  if (!dev_->open()) {
    logger_.Log("couldn't open device");
    return;
  }

  ArpPoisoningDetectionCookie cookie;
  if (!capture_wrapper_.StartCapture(dev_, PacketReceiver::onPacketArrivesArpPoisoningDetection, &cookie,
                                     last_task_id_))
    return;
  while (IsRunning()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  capture_wrapper_.StopCapture(dev_);
  End();
  logger_.Log("ArpPoisonDetection task finished.\n");
}

ashk::tasks::ArpPoisonDetectionTask::ArpPoisonDetectionTask(pcpp::IPv4Address iface_ip, int last_task_id) : iface_ip_(
    iface_ip), Task(last_task_id) {

}

std::string ashk::tasks::ArpPoisonDetectionTask::GetData(tasks_data_id data_id) {
  if (!extractable_data_.count(data_id))
    return "";
  switch (data_id) {
    default:return "";
  }
}
