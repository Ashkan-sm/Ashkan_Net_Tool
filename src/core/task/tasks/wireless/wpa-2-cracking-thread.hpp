//
// Created by dev on 8/6/25.
//

#ifndef ASHKANTOOL_WPA_2_CRACKING_THREAD_HPP
#define ASHKANTOOL_WPA_2_CRACKING_THREAD_HPP

#include <openssl/hmac.h>
#include <openssl/cmac.h>
#include <openssl/evp.h>
#include <openssl/sha.h>

#include "core/task/task.hpp"
#include "core/data-holders/wifi.hpp"

#define SHA1_DIGEST_LENGTH 20
namespace ashk::tasks {
class WPA2CrackingThread : public Task {
 public:
  explicit WPA2CrackingThread(long long int start_idx,
                              long long int end_idx,
                              long long int epol_ofset,
                              unsigned char *seed,
                              std::shared_ptr<HandShakeData> handshake_data,
                              Task *parent_task,
                              int last_task_id);
  std::string GetData(tasks_data_id data_id) override;
  int t = 0;
 private:
  Task *parent_task_;
  void Exec_() override;
  long long int start_idx_, end_idx_;
  std::shared_ptr<HandShakeData> handshake_data_;
  unsigned char *seed_;
  int eapol_offset_;
  static void Prf512(const unsigned char *key, int key_len,
                     const std::string &label,
                     const unsigned char *data, int data_len,
                     unsigned char *output, int output_len = 64);
  static std::string NumToPass(long long int n);

};
}

#endif //ASHKANTOOL_WPA_2_CRACKING_THREAD_HPP
