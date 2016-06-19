#include "lib/Encrypter.h"

using namespace std;

/**
 * Test if given plaintext can be encrypted/decrypted correctly using a hard-coded key
 */
void test(unsigned char plaintext[2]) {

    unsigned char keys[4];
    keys[0] = 0x47;
    keys[1] = 0x48;
    keys[2] = 0x3c;
    keys[3] = 0xf6;

    unsigned char plaintextResult[2];
    unsigned char cipherResult[2];

    Encrypter<0>::feistel(plaintext, cipherResult, keys, 4);
    Encrypter<0>::inverseFeistel(cipherResult, plaintextResult, keys, 4);

    if (plaintextResult[0] != plaintext[0]
        || plaintextResult[1] != plaintext[1]) {
        throw new exception();
    }
}

int main() {

    unsigned char plaintextTest[3][2];
    plaintextTest[0][0] = 0x01;
    plaintextTest[0][1] = 0x02;

    plaintextTest[1][0] = 0x03;
    plaintextTest[1][1] = 0x04;

    plaintextTest[2][0] = 0x12;
    plaintextTest[2][1] = 0x34;

    test(plaintextTest[0]);
    test(plaintextTest[1]);
    test(plaintextTest[2]);

    unsigned char plaintext[2][2];
    plaintext[0][0] = 0x00;
    plaintext[0][1] = 0x00;
    plaintext[1][0] = 0x12;
    plaintext[1][1] = 0x34;

    test(plaintext[0]);

    unsigned char cipher[2][2];
    cipher[0][0] = 0x47;
    cipher[0][1] = 0x48;
    cipher[1][0] = 0x3c;
    cipher[1][1] = 0xf6;

    unsigned char keys[2][4];

    Encrypter<0>::mitm(
            plaintext,
            cipher,
            keys
    );

    // print the found keysets
    for (int i = 0; i < 2; i++) {

        bitset<8> k1(keys[i][0]);
        bitset<8> k2(keys[i][1]);
        bitset<8> k3(keys[i][2]);
        bitset<8> k4(keys[i][3]);

        cout << k1 << k2 << k3 << k4 << endl;
    }

    return 0;
}
