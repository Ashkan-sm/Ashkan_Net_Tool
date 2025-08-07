// Created by dev on 6/5/25.
//

#include "net-core.hpp"



ashk::NetCore::NetCore()=default;


int ashk::NetCore::DiscoverInterface() {
std::vector<pcpp::PcapLiveDevice *> deviceList = pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();

for (auto i: deviceList) {
    if (i->getIPv4Address() != pcpp::IPv4Address("0.0.0.0") &&
        i->getIPv4Address() != pcpp::IPv4Address("127.0.0.1")) {
        dev_ = i;
        return 1;
    }
}

return 0;
}
std::vector<pcpp::PcapLiveDevice *> ashk::NetCore::DiscoverInterfaces() {
return pcpp::PcapLiveDeviceList::getInstance().getPcapLiveDevicesList();
}
pcpp::IPv4Address ashk::NetCore::InterfaceIp() {
  DiscoverInterface();
return dev_->getIPv4Address();
}

void ashk::NetCore::StartArpPoisoning(pcpp::IPv4Address iface_ip, pcpp::IPv4Address vic_src_ip,
                                      pcpp::IPv4Address vic_dst_ip,
                                      pcpp::IPv4Address forward_to_ip) {

  tasks_[last_added_task_id_] = std::make_unique<tasks::ArpPoisoningTask>(dev_, vic_src_ip, vic_dst_ip, forward_to_ip, iface_ip, last_added_task_id_);
  tasks_[last_added_task_id_]->Start();
last_added_task_id_++;
}

void ashk::NetCore::AddLoggerMethod(const std::function<void(const std::string &)> &method) {
  logger_.AddLogMethod(method);
}


void ashk::NetCore::EndTask(int id) {
  tasks_[id]->End();
  utils::Logger::getInstance().Log("Sent end signal to task\n");

}

std::vector<int> ashk::NetCore::GetRunningTasks() {
std::vector<int> out;
for (const auto &i: tasks_) {
    if (i.second->IsRunning()) {
        out.push_back(i.first);
    }
}
return out;
}

void ashk::NetCore::StartArpPoisonDetection(pcpp::IPv4Address iface_ip) {
  tasks_[last_added_task_id_]=std::make_unique<tasks::ArpPoisonDetectionTask>(iface_ip, last_added_task_id_);
  tasks_[last_added_task_id_]->Start();
last_added_task_id_++;

}

void ashk::NetCore::SendArpReq(pcpp::IPv4Address iface_ip, pcpp::IPv4Address ip) {
dev_ = pcpp::PcapLiveDeviceList::getInstance().getDeviceByIp(iface_ip);
if (dev_ == nullptr) {
  logger_.Log("couldn't find device\n");
    return;
}
if (!dev_->open()) {
  logger_.Log("couldn't open device");
    return;
}
pcpp::Packet arpRequest(100);

pcpp::EthLayer ethLayer(dev_->getMacAddress(), pcpp::MacAddress::Broadcast);
pcpp::ArpLayer arpLayer(pcpp::ArpRequest(dev_->getMacAddress(), iface_ip, ip));

if (!arpRequest.addLayer(&ethLayer))
{
  logger_.Log("Couldn't build Eth layer for ARP request");
    return;
}

if (!arpRequest.addLayer(&arpLayer))
{
  logger_.Log("Couldn't build ARP layer for ARP request\n");
    return;
}
arpRequest.computeCalculateFields();
if(!dev_->sendPacket(&arpRequest)) {
  logger_.Log("Unable to send Packet\n");
    return;
}
  logger_.Log("Sent arp request\n");
}

pcpp::MacAddress ashk::NetCore::Arp(pcpp::IPv4Address ip) {
return NetUtils::Arp(ip, dev_);
}


void ashk::NetCore::StartMitmForwarding(pcpp::IPv4Address iface_ip
                                     , pcpp::IPv4Address victim_ip
                                     , pcpp::IPv4Address gateway_ip, pcpp::MacAddress victim_mac, pcpp::MacAddress gateway_mac) {
  tasks_[last_added_task_id_]=std::make_unique<tasks::MITMPacketForwarding>(iface_ip, victim_ip, gateway_ip, victim_mac, gateway_mac, last_added_task_id_);
  tasks_[last_added_task_id_]->Start();
    last_added_task_id_++;
}

void ashk::NetCore::StartVlanHopping(pcpp::IPv4Address iface_ip, int outer_id, int inner_id) {
  tasks_[last_added_task_id_]=std::make_unique<tasks::VlanHoppingTask>(dev_, iface_ip, outer_id, inner_id, last_added_task_id_);
  tasks_[last_added_task_id_]->Start();
    last_added_task_id_++;
}

void ashk::NetCore::StartDtpNegotiation(pcpp::IPv4Address iface_ip, const std::string &domain_name) {
  tasks_[last_added_task_id_]=std::make_unique<tasks::DTPNegotiation>(dev_, iface_ip, domain_name, last_added_task_id_);
  tasks_[last_added_task_id_]->Start();
    last_added_task_id_++;
}

void ashk::NetCore::StartDtpDomainExtraction(pcpp::IPv4Address iface_ip, char *buffer) {
  tasks_[last_added_task_id_]=std::make_unique<tasks::DtpDomainExtraction>(dev_, iface_ip, buffer, last_added_task_id_);
  tasks_[last_added_task_id_]->Start();
    last_added_task_id_++;
}

void ashk::NetCore::StartDetectingWifiAps(std::string iface_name_or_ip, std::vector<WifiAp> &ap_list) {
  tasks_[last_added_task_id_]=std::make_unique<tasks::WifiApScanningTask>(dev_, iface_name_or_ip, ap_list, last_added_task_id_);
  tasks_[last_added_task_id_]->Start();
    last_added_task_id_++;
}

std::string ashk::NetCore::InterfaceName() {
  DiscoverInterface();
    return dev_->getName();
}

void ashk::NetCore::StartDetectingWifiHosts(const std::string &iface_ip_name_str,
                                            std::vector<std::shared_ptr<WifiHost>> &host_list) {
  tasks_[last_added_task_id_]=std::make_unique<tasks::WifiHostScanningTask>(dev_, iface_ip_name_str, host_list, last_added_task_id_);
  tasks_[last_added_task_id_]->Start();
    last_added_task_id_++;

}

void ashk::NetCore::StartSendingDeauthPackets(const std::string &iface_ip_name_str,
                                              WifiAp* wifi_ap,
                                              std::vector<std::shared_ptr<WifiHost>> &host_list) {
  tasks_[last_added_task_id_]=std::make_unique<tasks::DeauthPacketSendingTask>(dev_, iface_ip_name_str, *wifi_ap, host_list, last_added_task_id_);
  tasks_[last_added_task_id_]->Start();
    last_added_task_id_++;
}

void ashk::NetCore::StartPasswordCracking(const std::string &iface_ip_name_str, std::shared_ptr<HandShakeData> handshake_data) {
  tasks_[last_added_task_id_]=std::make_unique<tasks::WifiPasswordCrackingTask>(dev_, iface_ip_name_str, handshake_data, last_added_task_id_);
  tasks_[last_added_task_id_]->Start();
    last_added_task_id_++;
}

void ashk::NetCore::StartWpa2HandshakeCapturing(const std::string &iface_ip_name_str, std::shared_ptr<HandShakeData> handshake_data) {
  tasks_[last_added_task_id_]=std::make_unique<tasks::WPA2HandShakeCaptureTask>(dev_, iface_ip_name_str, handshake_data, last_added_task_id_);
  tasks_[last_added_task_id_]->Start();
    last_added_task_id_++;
}

