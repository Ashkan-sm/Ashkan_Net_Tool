//
// Created by dev on 8/4/25.
//

#include "wifi-password-cracking-task.hpp"

#include <utility>

ashk::tasks::WifiPasswordCrackingTask::WifiPasswordCrackingTask(pcpp::PcapLiveDevice *dev, std::string iface_name_or_ip,
                                                                std::shared_ptr<HandShakeData> handshake_data, int last_task_id) : Task(last_task_id),iface_name_or_ip(std::move(iface_name_or_ip))
                                                                ,handshake_data(std::move(handshake_data)) {

}

std::string ashk::tasks::WifiPasswordCrackingTask::get_data(ashk::tasks_data_id data_id) {
    return std::string();
}
#include "wifi-password-cracking-task.hpp"
#include <openssl/evp.h>
#include <openssl/cmac.h>
#include <iostream>

void print_hex(const uint8_t* data, size_t len) {
    for (size_t i = 0; i < len; ++i)
        printf("%02x", data[i]);
    printf("\n");
}

void prf512(const uint8_t* key, const char* label,
            const uint8_t* data, size_t data_len,
            uint8_t* output) {
    const size_t ptk_len = 64; // Desired output
    const size_t hmac_len = 20; // SHA1 output
    uint8_t digest[EVP_MAX_MD_SIZE];
    unsigned int digest_len;

    size_t label_len = strlen(label);
    size_t pos = 0;
    uint8_t counter = 1;

    while (pos < ptk_len) {
        // Construct message: label + 0x00 + data + counter
        std::vector<uint8_t> msg;
        msg.insert(msg.end(), label, label + label_len);
        msg.push_back(0x00);
        msg.insert(msg.end(), data, data + data_len);
        msg.push_back(counter);

        HMAC(EVP_sha1(), key, 32, msg.data(), msg.size(), digest, &digest_len);

        size_t copy_len = std::min((size_t)hmac_len, ptk_len - pos);
        memcpy(output + pos, digest, copy_len);
        pos += copy_len;
        counter++;
    }
}


void ashk::tasks::WifiPasswordCrackingTask::exec() {
    // 1. Print all inputs
    std::cout << "\n=== INPUT VERIFICATION ===\n";
    std::cout << "SSID: '" << handshake_data->selected_ap->e_ssid << "' (len: "
              << handshake_data->selected_ap->e_ssid.length() << ")\n";

    std::cout << "AP MAC: ";
    print_hex(handshake_data->selected_ap->b_ssid.getRawData(), 6);

    std::cout << "STA MAC: ";
    print_hex(handshake_data->station_mac.getRawData(), 6);

    std::cout << "ANonce: ";
    print_hex(handshake_data->ANonce, 32);

    std::cout << "SNonce: ";
    print_hex(handshake_data->SNonce, 32);

    std::cout << "EAPOL frame (" << handshake_data->eapol_size << " bytes):\n";
    print_hex(handshake_data->eapol, handshake_data->eapol_size);

    std::cout << "Captured MIC: ";
    print_hex(handshake_data->MIC, 16);

    // 2. Verify EAPOL frame structure
    std::cout << "\n=== EAPOL FRAME STRUCTURE ===\n";
    if (handshake_data->eapol_size < 81 + 16) {
        std::cerr << "ERROR: EAPOL frame too small (needs at least 97 bytes)\n";
        return;
    }

    // Check EAPOL header (Message 2 should be 01 03 00 XX 02 01)
    if (handshake_data->eapol[0] != 0x01 || handshake_data->eapol[1] != 0x03 ||
        handshake_data->eapol[4] != 0x02 || handshake_data->eapol[5] != 0x01) {
        std::cerr << "WARNING: Unexpected EAPOL header format\n";
    }

    // 3. Print MIC position context
    std::cout << "Bytes around MIC position (offset 81):\n";
    int start = std::max(0, 81 - 16);
    int end = std::min((int)handshake_data->eapol_size, 81 + 32);
    print_hex(handshake_data->eapol + start, end - start);

    // 4. PMK Calculation
    std::cout << "\n=== PMK CALCULATION ===\n";
    uint8_t pmk[32];
    PKCS5_PBKDF2_HMAC_SHA1("00000000", 8,
                           (uint8_t *)handshake_data->selected_ap->e_ssid.c_str(),
                           handshake_data->selected_ap->e_ssid.length(),
                           4096, 32, pmk);
    std::cout << "PMK: ";
    print_hex(pmk, 32);

    // 5. PTK Seed Construction
    std::cout << "\n=== PTK SEED ===\n";
    uint8_t seed[100];
    const uint8_t *mac1 = (memcmp(handshake_data->selected_ap->b_ssid.getRawData(),
                                  handshake_data->station_mac.getRawData(), 6) < 0)
                          ? handshake_data->selected_ap->b_ssid.getRawData()
                          : handshake_data->station_mac.getRawData();

    const uint8_t *mac2 = (mac1 == handshake_data->selected_ap->b_ssid.getRawData())
                          ? handshake_data->station_mac.getRawData()
                          : handshake_data->selected_ap->b_ssid.getRawData();

    const uint8_t *nonce1 = (memcmp(handshake_data->ANonce, handshake_data->SNonce, 32) < 0)
                            ? handshake_data->ANonce
                            : handshake_data->SNonce;

    const uint8_t *nonce2 = (nonce1 == handshake_data->ANonce)
                            ? handshake_data->SNonce
                            : handshake_data->ANonce;

    memcpy(seed, mac1, 6);
    memcpy(seed + 6, mac2, 6);
    memcpy(seed + 12, nonce1, 32);
    memcpy(seed + 44, nonce2, 32);

    std::cout << "Seed: ";
    print_hex(seed, 6 + 6 + 32 + 32);

    // 6. PTK Derivation
    std::cout << "\n=== PTK DERIVATION ===\n";
    uint8_t ptk[64];
    prf512(pmk, "Pairwise key expansion", seed, 6 + 6 + 32 + 32, ptk);
    std::cout << "PTK: ";
    print_hex(ptk, 64);
    std::cout << "KCK (first 16 bytes): ";
    print_hex(ptk, 16);

    // 7. MIC Calculation
    std::cout << "\n=== MIC CALCULATION ===\n";
    uint8_t mic[20];
    uint8_t eapol_copy[200];
    memcpy(eapol_copy, handshake_data->eapol, handshake_data->eapol_size);
    memset(eapol_copy + 81, 0, 16); // Zero out MIC

    HMAC(EVP_sha1(), ptk, 16, eapol_copy, handshake_data->eapol_size, mic, nullptr);
    std::cout << "Calculated MIC: ";
    print_hex(mic, 16);

    std::cout << "Expected MIC:   ";
    print_hex(handshake_data->MIC, 16);

    // 8. Final Verification
    std::cout << "\n=== VERIFICATION ===\n";
    if (memcmp(mic, handshake_data->MIC, 16) == 0) {
        std::cout << "MATCH: MIC verification successful!\n";
    } else {
        std::cout << "MISMATCH: MIC verification failed!\n";
        std::cout << "Possible causes:\n";
        std::cout << "1. Wrong passphrase (used '00000000')\n";
        std::cout << "2. Incorrect EAPOL frame extraction\n";
        std::cout << "3. Wrong MIC position (used offset 81)\n";
        std::cout << "4. MAC/nonce ordering error\n";
    }
}