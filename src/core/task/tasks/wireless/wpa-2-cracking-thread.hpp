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
  std::string get_data(tasks_data_id data_id) override;
  int t = 0;
 private:
  Task *parent_task;
  void exec() override;
  long long int start_idx, end_idx;
  std::shared_ptr<HandShakeData> handshake_data;
  unsigned char *seed;
  int epol_ofset;
  static void prf_512(const unsigned char *key, int key_len,
                      const std::string &label,
                      const unsigned char *data, int data_len,
                      unsigned char *output, int output_len = 64);
  static std::string num_to_pass(long long int n);

};
}

#endif //ASHKANTOOL_WPA_2_CRACKING_THREAD_HPP
