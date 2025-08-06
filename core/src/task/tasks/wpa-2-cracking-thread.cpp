//
// Created by dev on 8/6/25.
//

#include "wpa-2-cracking-thread.hpp"

#include <utility>

ashk::tasks::WPA2CrackingThread::WPA2CrackingThread(int start_idx, int end_idx, int epol_ofset, unsigned char *seed,
                                                    std::shared_ptr<HandShakeData> handshake_data, int last_task_id): Task(last_task_id),start_idx(start_idx),end_idx(end_idx)
                                                    ,epol_ofset(epol_ofset)
                                                    ,seed(seed)
                                                    ,handshake_data(std::move(handshake_data)){


                                                    }

const char chars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
std::string ashk::tasks::WPA2CrackingThread::num_to_pass(int n) {

    int num=10;

    std::string out;
    while(n>=0){
        out+=chars[n%num];
        n=n/num;
    }
    std::cout<<out<<std::endl;
    return std::move(out);
}

void ashk::tasks::WPA2CrackingThread::prf_512(const unsigned char* key, int key_len,
             const std::string& label,
             const unsigned char* data, int data_len,
             unsigned char* output, int output_len) {

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
std::string ashk::tasks::WPA2CrackingThread::get_data(ashk::tasks_data_id data_id) {
    if(!extractable_data.count(data_id))
        return "";
    switch (data_id) {
        case WPA2_CRACK_T:
            return std::to_string(t);
        default:
            return "";
    }
}

void ashk::tasks::WPA2CrackingThread::exec() {
    uint8_t pmk[32];
    uint8_t mic[20];
    uint8_t ptk[64];
    std::string password;
    for(int i=start_idx;i<end_idx && is_running();i++) {
        t++;
        password= num_to_pass(i);
        std::cout<<i<<" "<<password<<std::endl;
        PKCS5_PBKDF2_HMAC_SHA1(password.c_str(), 8,
                               (uint8_t *) handshake_data->selected_ap->e_ssid.c_str(),
                               handshake_data->selected_ap->e_ssid.length(),
                               4096, 32, pmk);


        prf_512(pmk, 32, "Pairwise key expansion", seed, 6 + 6 + 32 + 32, ptk);

        memset(handshake_data->eapol + epol_ofset, 0, 16); // Zero out MIC
        HMAC(EVP_sha1(), ptk, 16, handshake_data->eapol, handshake_data->eapol_size, mic, nullptr);

        if (memcmp(mic, handshake_data->MIC, 16) == 0) {
            std::cout << "PASSWORD: " << password << std::endl;
            ashk::utils::Logger::getInstance().log("PASSWORD: "+password+"\n");
            break;
        }
    }
}





