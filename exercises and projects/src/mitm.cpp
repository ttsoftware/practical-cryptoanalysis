#include "lib/Encrypter.h"

using namespace std;

int main() {

    unsigned char plaintext[2][2];
    plaintext[0][0] = 0x00000000;
    plaintext[0][1] = 0x00000000;
    plaintext[1][0] = 0x00000012;
    plaintext[1][1] = 0x00000034;

    unsigned char cipher[2][2];
    cipher[0][0] = 0x00000047;
    cipher[0][1] = 0x00000048;
    cipher[1][0] = 0x0000003c;
    cipher[1][1] = 0x000000f6;

    unsigned char keys[4];

    Encrypter<0>::mitm(
            plaintext,
            cipher,
            keys
    );

    cout << "all keys" << endl;
    cout << keys[0] << endl;
    cout << keys[1] << endl;
    cout << keys[2] << endl;
    cout << keys[3] << endl;

    unsigned char plaintextResult[2];
    unsigned char cipherResult[2];

    Encrypter<0>::feistel(cipher[0], plaintextResult, keys, 4);
    Encrypter<0>::feistel(plaintext[0], cipherResult, keys, 4);

    if (plaintextResult[0] == plaintext[0][0]
        && plaintextResult[1] == plaintext[0][1]) {
        cout << "winning!" << endl;
    }

    if (cipherResult[0] == cipher[0][0]
        && cipherResult[1] == cipher[0][1]) {
        cout << "winning!" << endl;
    }

    return 0;
}
