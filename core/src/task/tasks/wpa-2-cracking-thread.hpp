//
// Created by dev on 8/6/25.
//

#ifndef ASHKANTOOL_WPA_2_CRACKING_THREAD_HPP
#define ASHKANTOOL_WPA_2_CRACKING_THREAD_HPP
#include "task-headers.hpp"
#include <openssl/hmac.h>
#include <openssl/cmac.h>
#include <openssl/evp.h>
#include <openssl/sha.h>
#define SHA1_DIGEST_LENGTH 20
namespace ashk::tasks {
    class WPA2CrackingThread : public Task{
    public:
        explicit WPA2CrackingThread(int start_idx,int end_idx,int epol_ofset,unsigned char * seed,
                                    std::shared_ptr<HandShakeData> handshake_data,int last_task_id);
        std::string get_data(tasks_data_id data_id) override;
        int t=0;
    private:
        void exec() override;
        int start_idx,end_idx;
        std::shared_ptr<HandShakeData> handshake_data;
        unsigned char * seed;
        int epol_ofset;
        static void prf_512(const unsigned char* key, int key_len,
                const std::string& label,
                const unsigned char* data, int data_len,
                unsigned char* output, int output_len = 64);
        static std::string num_to_pass(int n);

    };
}


#endif //ASHKANTOOL_WPA_2_CRACKING_THREAD_HPP
