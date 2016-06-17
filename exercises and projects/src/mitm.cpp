#include "lib/Encrypter.h"

using namespace std;

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
