#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <sstream>
#include <random>
#include <openssl/des.h>

using namespace std;

struct PasswordRecord {
    unsigned short salt;
    string hash;
};

string toHex(const unsigned char data[], int size) {
    stringstream ss;
    ss << hex << setfill('0');

    for (int i = 0; i < size; i++) {
        ss << setw(2) << (int)data[i];
    }

    return ss.str();
}

unsigned short generateSalt() {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<unsigned short> dist(0, 65535);
    return dist(gen);
}

void makeKey(string password, DES_cblock &key) {
    for (int i = 0; i < 8; i++) {
        if (i < password.length()) {
            key[i] = (password[i] & 0x7F) << 1;
        } else {
            key[i] = 0;
        }
    }
}
