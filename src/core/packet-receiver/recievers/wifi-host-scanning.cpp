#include "core/packet-receiver/packet-receiver.hpp"
#include <algorithm>

void ashk::PacketReceiver::onPacketArrivesWifiHostScanning(pcpp::RawPacket *raw_pcap_packet, pcpp::PcapLiveDevice *dev,
                                                           void *cookie) {
  auto *data = static_cast<WifiHostScanningCookie *>(cookie);
//    data->ap_list->push_back({"yoo"});
  const uint8_t *raw_packet = raw_pcap_packet->getRawData();

  const uint8_t *wifi_layer;
  if (htonl(*reinterpret_cast<const uint32_t *>(raw_packet)) == 0x44000000) {//parism header
    uint32_t prism_header_length = *reinterpret_cast<const uint32_t *>(raw_packet + 4);
    wifi_layer = raw_packet + prism_header_length;
  } else if (raw_packet[0] == 0x00) {//readio header
    uint16_t radio_header_length = *reinterpret_cast<const uint16_t *>(raw_packet + 2);
    wifi_layer = raw_packet + radio_header_length;
  } else {
    return;
  }

  uint16_t wifi_layer_type = htons(*reinterpret_cast<const uint16_t *>(wifi_layer));

  uint8_t transmiter_mac_adr[6];
  if (wifi_layer + 16 <= raw_packet + raw_pcap_packet->getRawDataLen()) {
    memcpy(transmiter_mac_adr, wifi_layer + 10, 6);
  }

  std::shared_ptr<WifiHost> out = std::make_unique<WifiHost>(pcpp::MacAddress(transmiter_mac_adr), false);
  if (std::find_if(data->host_list->begin(),
                   data->host_list->end(),
                   [&out](const auto &a) { return a->mac == out->mac; }) == data->host_list->end())
    data->host_list->push_back(std::make_unique<WifiHost>(pcpp::MacAddress(transmiter_mac_adr), false));

}

