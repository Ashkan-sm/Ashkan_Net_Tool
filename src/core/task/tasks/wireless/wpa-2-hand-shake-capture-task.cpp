//
// Created by dev on 8/3/25.
//

#include "wpa-2-hand-shake-capture-task.hpp"

#include <utility>

ashk::tasks::WPA2HandShakeCaptureTask::WPA2HandShakeCaptureTask(pcpp::PcapLiveDevice *dev, std::string iface_name_or_ip,
                                                                std::shared_ptr<HandShakeData> data, int last_task_id)
    : Task(last_task_id),
      dev_(dev),
      iface_name_or_ip_(std::move(iface_name_or_ip)),
      data_(data) {

}

std::string ashk::tasks::WPA2HandShakeCaptureTask::GetData(tasks_data_id data_id) {
  return std::string();
}

void ashk::tasks::WPA2HandShakeCaptureTask::Exec_() {
  logger_.Log("start capturing wpa2 handshake . . .\n");
  dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIpOrName(iface_name_or_ip_);
  if (dev_ == nullptr) {
    logger_.Log("couldn't find device\n");
    return;
  }
  if (!dev_->open()) {
    logger_.Log("couldn't open device");
    return;
  }

  WPA2HandShakeCapturingCookie cookie(data_, this);
  if (!capture_wrapper_.StartCapture(dev_,
                                     PacketReceiver::onPacketArrivesWPA2HandShakeCapturing,
                                     &cookie,
                                     last_task_id_)) {
    return;
  }
  while (IsRunning()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  capture_wrapper_.StopCapture(dev_);
  End();
  logger_.Log("handshake capturing finished\n");
}
