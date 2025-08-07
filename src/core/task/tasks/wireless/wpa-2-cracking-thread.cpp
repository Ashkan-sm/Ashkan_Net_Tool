//
// Created by dev on 8/6/25.
//

#include "wpa-2-cracking-thread.hpp"

#include <utility>

ashk::tasks::WPA2CrackingThread::WPA2CrackingThread(long long int start_idx,
                                                    long long int end_idx,
                                                    long long int epol_ofset,
                                                    unsigned char *seed,
                                                    std::shared_ptr<HandShakeData> handshake_data,
                                                    Task *parent_task,
                                                    int last_task_id)
    : Task(last_task_id),
      start_idx_(start_idx),
      end_idx_(end_idx),
      eapol_offset_(epol_ofset),
      seed_(seed),
      handshake_data_(std::move(handshake_data)),
      parent_task_(parent_task) {

}

const char chars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
std::string ashk::tasks::WPA2CrackingThread::NumToPass(long long int n) {

  int num = 10;

  std::string out;
  do {
    out += chars[n % num];
    n = n / num;
  } while (n > 0);

  return std::move(out);
}

void ashk::tasks::WPA2CrackingThread::Prf512(const unsigned char *key, int key_len,
                                             const std::string &label,
                                             const unsigned char *data, int data_len,
                                             unsigned char *output, int output_len) {

  unsigned int md_len;
  unsigned char digest[SHA1_DIGEST_LENGTH];
  int iterations = (output_len + SHA1_DIGEST_LENGTH - 1) / SHA1_DIGEST_LENGTH;

  int pos = 0;
  for (int i = 0; i < iterations; ++i) {
    std::vector<unsigned char> input;
    input.insert(input.end(), label.begin(), label.end());
    input.push_back(0x00);  // null byte separator
    input.insert(input.end(), data, data + data_len);
    input.push_back(static_cast<unsigned char>(i));

    HMAC(EVP_sha1(), key, key_len, input.data(), input.size(), digest, &md_len);

    int copy_len = std::min(output_len - pos, SHA1_DIGEST_LENGTH);
    memcpy(output + pos, digest, copy_len);
    pos += copy_len;
  }
}
std::string ashk::tasks::WPA2CrackingThread::GetData(tasks_data_id data_id) {
  if (!extractable_data_.count(data_id))
    return "";
  switch (data_id) {
    case WPA2_CRACK_T:return std::to_string(t);
    default:return "";
  }
}

void ashk::tasks::WPA2CrackingThread::Exec_() {
  uint8_t pmk[32];
  uint8_t mic[20];
  uint8_t ptk[64];
  std::string password;

  for (long long int i = start_idx_; i < end_idx_ && IsRunning(); i++) {
    t++;

    password = NumToPass(i);

    PKCS5_PBKDF2_HMAC_SHA1(password.c_str(), 8,
                           (uint8_t *) handshake_data_->selected_ap->e_ssid.c_str(),
                           handshake_data_->selected_ap->e_ssid.length(),
                           4096, 32, pmk);

    Prf512(pmk, 32, "Pairwise key expansion", seed_, 6 + 6 + 32 + 32, ptk);

    memset(handshake_data_->eapol + eapol_offset_, 0, 16); // Zero out MIC
    HMAC(EVP_sha1(), ptk, 16, handshake_data_->eapol, handshake_data_->eapol_size, mic, nullptr);

    if (memcmp(mic, handshake_data_->MIC, 16) == 0) {
      ashk::utils::Logger::getInstance().Log("PASSWORD: " + password + "\n");
      parent_task_->End();
      break;
    }
  }

}





