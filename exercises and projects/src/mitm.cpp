#include "lib/Encrypter.h"

using namespace std;

void test(unsigned char plaintext[2][2]) {

    unsigned char keys[4];
    keys[0] = 0x00;
    keys[1] = 0x01;
    keys[2] = 0x02;
    keys[3] = 0x03;

    unsigned char plaintextResult[2];
    unsigned char cipherResult[2];

    Encrypter<0>::feistel(plaintext[0], cipherResult, keys, 4);
    Encrypter<0>::inverseFeistel(cipherResult, plaintextResult, keys, 4);

    bitset<8> b1 (cipherResult[0]);
    bitset<8> b2 (cipherResult[1]);

    bitset<8> p1 (plaintextResult[0]);
    bitset<8> p2 (plaintextResult[1]);

    bitset<8> p3 (plaintext[0][0]);
    bitset<8> p4 (plaintext[0][1]);

    cout << b1 << b2 << endl;
    cout << p1 << p2 << endl;
    cout << p3 << p4 << endl;

    cout << (p1 == p3 && p2 == p4) << endl;

    if (p1 == p3 && p2 == p4) {

    }
}

int main() {

    unsigned char plaintext[2][2];
    plaintext[0][0] = 0x00;
    plaintext[0][1] = 0x00;
    plaintext[1][0] = 0x12;
    plaintext[1][1] = 0x34;

    unsigned char cipher[2][2];
    cipher[0][0] = 0x47;
    cipher[0][1] = 0x48;
    cipher[1][0] = 0x3c;
    cipher[1][1] = 0xf6;

    unsigned char keys[4];

    test(plaintext);

    Encrypter<0>::mitm(
            plaintext,
            cipher,
            keys
    );

    unsigned char cipherResult[2];

    Encrypter<0>::feistel(plaintext[0], cipherResult, keys, 4);

    if (cipherResult[0] == cipher[0][0]
        && cipherResult[1] == cipher[0][1]) {
        cout << "success" << endl;
    }

    return 0;
}
