
#include "core/packet-receiver/packet-receiver.hpp"

void ashk::PacketReceiver::onPacketArrivesWPA2HandShakeCapturing(pcpp::RawPacket *raw_pcap_packet,
                                                                 pcpp::PcapLiveDevice *dev,
                                                                 void *cookie) {

  auto *data = static_cast<WPA2HandShakeCapturingCookie *>(cookie);
  if (!data->task->IsRunning())
    return;

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
  uint8_t wifi_layer_version = *reinterpret_cast<const uint8_t *>(wifi_layer);
  uint8_t wifi_layer_type = *reinterpret_cast<const uint8_t *>(wifi_layer + 1);
  uint8_t transmitter_mac[6];
  if (wifi_layer + 16 <= raw_packet + raw_pcap_packet->getRawDataLen()) {
    memcpy(transmitter_mac, wifi_layer + 10, 6);
  } else return;
  uint8_t destination_mac[6];
  if (wifi_layer + 10 <= raw_packet + raw_pcap_packet->getRawDataLen()) {
    memcpy(destination_mac, wifi_layer + 4, 6);
  } else return;
  int wifi_layer_length;
  if (wifi_layer_version == 0x88) {
    wifi_layer_length = 26;
  } else if (wifi_layer_version == 0x08) {
    wifi_layer_length = 24;
  } else {
    return;
  }
  const uint8_t *llc_layer = wifi_layer + wifi_layer_length;
  if (wifi_layer_type == 0x02) {//from ap to station
    if (data->hand_shake_data->selected_ap->b_ssid != pcpp::MacAddress(transmitter_mac))
      return;

    static const uint8_t expected_llc_layer[] = {0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00, 0x88, 0x8e};
    if (memcmp(llc_layer, expected_llc_layer, 8) != 0) {
      return;
    }
    const uint8_t *wpa2_layer = llc_layer + 8;
    uint16_t key_information = htons(*reinterpret_cast<const uint16_t *>(wpa2_layer + 5));

    if (key_information != 0x008a) {
      return;
    }
    memcpy(data->hand_shake_data->ANonce, wpa2_layer + 17, 32);
    data->hand_shake_data->station_mac = pcpp::MacAddress(destination_mac);
    data->hand_shake_data->got_msg_1 = true;
    return;
  } else if ((wifi_layer_type == 0x01) && data->hand_shake_data->got_msg_1) {//from station to ap
    if (data->hand_shake_data->selected_ap->b_ssid != pcpp::MacAddress(destination_mac)
        || data->hand_shake_data->station_mac != pcpp::MacAddress(transmitter_mac))
      return;
    static const uint8_t expected_llc_layer[] = {0xaa, 0xaa, 0x03, 0x00, 0x00, 0x00, 0x88, 0x8e};
    if (memcmp(llc_layer, expected_llc_layer, 8) != 0) {
      return;
    }
    const uint8_t *wpa2_layer = llc_layer + 8;
    uint16_t key_information = htons(*reinterpret_cast<const uint16_t *>(wpa2_layer + 5));

    if (key_information != 0x010a) {
      return;
    }
    memcpy(data->hand_shake_data->SNonce, wpa2_layer + 17, 32);
//        memcpy(data->hand_shake_data->MIC,wpa2_layer+81,16);
    data->hand_shake_data->eapol_size = htons(*reinterpret_cast<const uint16_t *>(wpa2_layer + 2)) + 4;

    memcpy(data->hand_shake_data->eapol, wpa2_layer, data->hand_shake_data->eapol_size);

    data->hand_shake_data->got_msg_2 = true;
    utils::Logger::getInstance().Log("captured handshake\n");
    data->task->End();
    return;

  } else
    return;

}