#include "Encrypter.h"

unsigned char secret[] = {
        0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5,
        0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
        0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0,
        0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
        0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc,
        0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
        0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a,
        0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
        0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0,
        0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
        0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b,
        0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
        0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85,
        0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
        0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5,
        0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
        0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17,
        0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
        0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88,
        0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
        0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c,
        0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
        0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9,
        0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
        0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6,
        0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
        0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e,
        0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
        0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94,
        0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
        0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68,
        0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16
};

template<size_t T>
bitset<16> Encrypter<T>::concat(bitset<8> inputA, bitset<8> inputB) {
    bitset<16> returnBits(0);
    // Concats bits from input B first, then A
    for (int i = 0; i < 8; ++i) {
        returnBits[i] = inputB[i];
    }
    for (int i = 8; i < 16; ++i) {
        returnBits[i] = inputA[i - 8];
    }
    return returnBits;
}

/*
 * balanced Feistel of 16 bit with the AES S-box
 */
template<size_t T>
void Encrypter<T>::feistel(unsigned char *plaintext,
                           unsigned char *cipher,
                           unsigned char *key,
                           int rounds) {

    unsigned char x[2], z;

    x[0] = plaintext[0];
    x[1] = plaintext[1];

    for (int i = 0; i < rounds; i++) {
        x[0] = x[0] ^ secret[key[i] ^ x[1]];
        z = x[0];
        x[0] = x[1];
        x[1] = z;

        if(rounds > 3){
            cout << x[0] << x[1] << endl;
        }
    }

    cipher[0] = x[0];
    cipher[1] = x[1];
}

template<size_t T>
void Encrypter<T>::inverseFeistel(unsigned char *plaintext,
                                  unsigned char *cipher,
                                  unsigned char *key,
                                  int rounds) {

    unsigned char x[2], z;

    x[0] = plaintext[1];
    x[1] = plaintext[0];

    for (int i = rounds - 1; i >= 0; i--) {
        x[0] = x[0] ^ secret[key[i] ^ x[1]];
        z = x[0];
        x[0] = x[1];
        x[1] = z;
    }

    cipher[0] = x[1];
    cipher[1] = x[0];
}

template<size_t T>
void Encrypter<T>::mitm(unsigned char plaintext[2][2],
                        unsigned char cipher[2][2],
                        unsigned char *returnKeys) {

    int keySpace = pow(2, 8);

    // map from cipher to keyset
    unordered_map<bitset<16>, unsigned char *> cipherTable;

    int x = 0;
    unsigned char firstKeys[keySpace * keySpace][4];

    // find all key combinations going forward
    for (int i = 0; i < keySpace; i++) {
        for (int j = 0; j < keySpace; j++) {

            unsigned char currentCipher[2];
            unsigned char keys[2];
            keys[0] = i;
            keys[1] = j;

            Encrypter<T>::feistel(plaintext[0], currentCipher, keys, 2);

            bitset<8> c1(currentCipher[0]);
            bitset<8> c2(currentCipher[1]);

            bitset<16> index = Encrypter<T>::concat(c1, c2);
            cipherTable[index] = keys;
        }
    }

    cout << cipherTable.size() << endl;

    // find all key combinations going backwards
    for (int i = 0; i < keySpace; i++) {
        for (int j = 0; j < keySpace; j++) {

            unsigned char currentPlaintext[2];
            unsigned char keys[2];
            keys[0] = i;
            keys[1] = j;

            Encrypter<T>::inverseFeistel(cipher[0], currentPlaintext, keys, 2);

            bitset<8> c1(currentPlaintext[0]);
            bitset<8> c2(currentPlaintext[1]);

            bitset<16> index = Encrypter<T>::concat(c1, c2);

            // does the current-plaintexts in exist in the ciphertables?
            if (cipherTable.find(index) != cipherTable.end()) {


                firstKeys[x][0] = cipherTable[index][0];
                firstKeys[x][1] = cipherTable[index][1];
                firstKeys[x][2] = (unsigned char) i;
                firstKeys[x][3] = (unsigned char) j;

                if(x == 46385){
                    cout << index << endl;
                    unsigned char test[2];
                    Encrypter<T>::feistel(plaintext[0], test, firstKeys[i], 4);
                    cout << cipher[0][0] << cipher[0][1] << endl;
                    cout << test[0] << test[1] << endl;
                }
                x++;
            }
        }
    }

    bitset<8> c1(cipher[0][0]);
    bitset<8> c2(cipher[0][1]);

    bitset<8> c3(cipher[1][0]);
    bitset<8> c4(cipher[1][1]);

    bitset<16> cipherBits0 = Encrypter<T>::concat(c1, c2);
    bitset<16> cipherBits1 = Encrypter<T>::concat(c3, c4);

    // find the cipher permutations of keys in returnKeys using plaintext[1]
    // check if a cipher exists which match a cipher in resultTable (going backwards)
    for (int i = 0; i < x; i++) {

        unsigned char cipherResult[2][2];

        Encrypter<T>::feistel(plaintext[1], cipherResult[0], firstKeys[i], 4);

        bitset<8> p1(cipherResult[0][0]);
        bitset<8> p2(cipherResult[0][1]);

        bitset<16> cc = Encrypter<T>::concat(p1, p2);

        if (cipherBits1 == cc) {
            cout << "i: " << i << endl;
            cout << "cc: " << cc << endl;

            Encrypter<T>::feistel(plaintext[0], cipherResult[1], firstKeys[i], 4);

            bitset<8> p3(cipherResult[1][0]);
            bitset<8> p4(cipherResult[1][1]);

            bitset<16> ccc = Encrypter<T>::concat(p3, p4);

            cout << "troelstest" << cipherBits0 << endl;
            cout << "troelstest" << ccc << endl;
            if (cipherBits0 == ccc) {

                cout << "ccc: " << ccc << endl;

                returnKeys = firstKeys[i];
            }
        }
    }
}