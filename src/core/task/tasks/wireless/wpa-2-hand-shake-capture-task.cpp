//
// Created by dev on 8/3/25.
//

#include "wpa-2-hand-shake-capture-task.hpp"

#include <utility>

ashk::tasks::WPA2HandShakeCaptureTask::WPA2HandShakeCaptureTask(pcpp::PcapLiveDevice *dev, std::string iface_name_or_ip,
                                                                std::shared_ptr<HandShakeData> data, int last_task_id)
    : Task(last_task_id),
      dev_(dev),
      iface_name_or_ip(std::move(iface_name_or_ip)),
      data(data) {

}

std::string ashk::tasks::WPA2HandShakeCaptureTask::get_data(ashk::tasks_data_id data_id) {
  return std::string();
}

void ashk::tasks::WPA2HandShakeCaptureTask::exec() {
  logger.log("start capturing wpa2 handshake . . .\n");
  dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIpOrName(iface_name_or_ip);
  if (dev_ == nullptr) {
    logger.log("couldn't find device\n");
    return;
  }
  if (!dev_->open()) {
    logger.log("couldn't open device");
    return;
  }

  WPA2HandShakeCapturingCookie cookie(data, this);
  if (!capture_wrapper.start_capture(dev_,
                                     PacketReceiver::onPacketArrivesWPA2HandShakeCapturing,
                                     &cookie,
                                     last_task_id)) {
    return;
  }
  while (is_running()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  capture_wrapper.stop_capture(dev_);
  end();
  logger.log("handshake capturing finished\n");
}
