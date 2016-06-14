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

    cout << "all keys" << endl;
    cout << keys[0] << endl;
    cout << keys[1] << endl;
    cout << keys[2] << endl;
    cout << keys[3] << endl;

    unsigned char foundCipher[2];

    Encrypter<0>::feistel(plaintext[0], foundCipher, keys, 4);

    cout << "cipher" << endl;
    cout << cipher[0][0] << endl;
    cout << cipher[0][1] << endl;

    cout << "found cipher" << endl;
    cout << foundCipher[0] << endl;
    cout << foundCipher[1] << endl;

    if (foundCipher[0] == 0x47
            && foundCipher[1] == 0x48) {
        cout << "succes" << endl;
    }

    return 0;
}
