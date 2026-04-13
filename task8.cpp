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

PasswordRecord encryptPassword(string password, unsigned short salt) {
    DES_cblock key;
    makeKey(password, key);

    DES_set_odd_parity(&key);

    DES_key_schedule schedule;
    DES_set_key_unchecked(&key, &schedule);

    DES_cblock block;
    DES_cblock output;

    unsigned char low = salt & 0xFF;
    unsigned char high = (salt >> 8) & 0xFF;


    for (int i = 0; i < 8; i++) {
        if (i % 2 == 0) {
            block[i] = low;
        } else {
            block[i] = high;
        }
    }

    
    for (int round = 0; round < 25; round++) {
        block[0] ^= low;
        block[1] ^= high;
        block[2] ^= (low >> 1) | (high << 7);
        block[3] ^= (high >> 1) | (low << 7);
        block[4] ^= low ^ high;
        block[5] ^= low + round;
        block[6] ^= high + round;
        block[7] ^= (low ^ high ^ round);

        DES_ecb_encrypt(&block, &output, &schedule, DES_ENCRYPT);

        for (int j = 0; j < 8; j++) {
            block[j] = output[j];
        }
    }

    PasswordRecord record;
    record.salt = salt;
    record.hash = toHex(output, 8);

    return record;
}


string storePassword(PasswordRecord record) {
    stringstream ss;
    ss << hex << setw(4) << setfill('0') << record.salt;
    ss << ":" << record.hash;
    return ss.str();
}

bool checkPassword(string inputPassword, string savedData) {
    int pos = savedData.find(':');

    string saltPart = savedData.substr(0, pos);
    string hashPart = savedData.substr(pos + 1);

    unsigned short salt;
    stringstream ss;
    ss << hex << saltPart;
    ss >> salt;

    PasswordRecord testRecord = encryptPassword(inputPassword, salt);

    return testRecord.hash == hashPart;
}

int main() {
    vector<string> passwords = {
        "orange12",
        "delta99",
        "sunRise7",
        "cairo2026",
        "desLab01",
        "secureMe",
        "passKey1",
        "zebra88",
        "moon1234",
        "taskeight"
    };

    vector<string> encryptedPasswords;

    cout << "Generated encrypted passwords:" << endl;
    cout << "-----------------------------" << endl;

    for (int i = 0; i < passwords.size(); i++) {
        unsigned short salt = generateSalt();
        PasswordRecord record = encryptPassword(passwords[i], salt);
        string stored = storePassword(record);

        encryptedPasswords.push_back(stored);

        cout << passwords[i] << " -> " << stored << endl;
    }

    cout << endl;
    cout << "Password validation test:" << endl;
    cout << "-------------------------" << endl;

    if (checkPassword("orange12", encryptedPasswords[0])) {
        cout << "orange12 is VALID for record 1" << endl;
    } else {
        cout << "orange12 is INVALID for record 1" << endl;
    }

    if (checkPassword("wrongpass", encryptedPasswords[0])) {
        cout << "wrongpass is VALID for record 1" << endl;
    } else {
        cout << "wrongpass is INVALID for record 1" << endl;
    }

    return 0;
}
