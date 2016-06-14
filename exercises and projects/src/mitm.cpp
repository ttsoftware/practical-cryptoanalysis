#include "lib/Encrypter.h"

using namespace std;

int main() {

    unsigned char plaintext[2];
    plaintext[0] = 0x00;
    plaintext[1] = 0x00;

    unsigned char cipher[2];
    cipher[0] = 0x47;
    cipher[1] = 0x48;

    unsigned char* keys = Encrypter<0>::mitm(
            plaintext,
            cipher
    );

    cout << "all keys" << endl;
    cout << keys[0] << endl;
    cout << keys[1] << endl;
    cout << keys[2] << endl;
    cout << keys[3] << endl;

    unsigned char foundCipher[2];

    Encrypter<0>::feistel(plaintext, foundCipher, keys, 4);

    cout << "cipher" << endl;
    cout << foundCipher[0] << endl;
    cout << foundCipher[1] << endl;

    return 0;
}
