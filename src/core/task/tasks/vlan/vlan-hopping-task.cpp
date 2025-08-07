//
// Created by dev on 6/10/25.
//

#include "vlan-hopping-task.hpp"

ashk::tasks::VlanHoppingTask::VlanHoppingTask(pcpp::PcapLiveDevice *dev,
                                              pcpp::IPv4Address iface_ip,
                                              int outer_id,
                                              int inner_id,
                                              int last_task_id) :
    dev_(dev),
    iface_ip_(iface_ip),
    outer_id_(outer_id),
    inner_id_(inner_id),
    Task(last_task_id) {

}

void ashk::tasks::VlanHoppingTask::Exec_() {
  logger_.Log("starting vlan hopping . . .\n");
  dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(iface_ip_);
  if (dev_ == nullptr) {
    logger_.Log("couldn't find device\n");
    return;
  }
  if (!dev_->open()) {
    logger_.Log("couldn't open device");
    return;
  }

  VlanHoppingCookie cookie{
      cookie.inner_id = inner_id_,
      cookie.outer_id = outer_id_
  };
  if (!capture_wrapper_.StartCapture(dev_, PacketReceiver::onPacketArrivesVlanHopping, &cookie, last_task_id_))
    return;
  while (IsRunning()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  capture_wrapper_.StopCapture(dev_);
  End();
  logger_.Log("vlan hopping task finished.\n");

}
std::string ashk::tasks::VlanHoppingTask::GetData(tasks_data_id data_id) {
  if (!extractable_data_.count(data_id))
    return "";
  switch (data_id) {
    default:return "";
  }
}
