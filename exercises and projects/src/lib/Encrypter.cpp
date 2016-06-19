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

/**
 * Concat two 8-bit bitsets into a single 16-bit bitset
 */
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

/**
 * Split a 16-bit bitset into two 8-bit bitsets
 */
template<size_t T>
tuple<bitset<8>, bitset<8>> Encrypter<T>::split(bitset<16> input) {

    bitset<8> b1(0);
    bitset<8> b2(0);

    for (int i = 0; i < input.size(); i++) {
        if (i >= 8) {
            b1[i - 8] = input[i];
        }
        if (i < 8) {
            b2[i] = input[i];
        }
    }

    tuple<bitset<8>, bitset<8>> temp(b1, b2);
    return temp;
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
    }

    cipher[0] = x[0];
    cipher[1] = x[1];
}

/**
 * Inverse feistel function - equivalent to going backwards up the chain
 */
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

/**
 * forward-encrypt 2 rounds of feistel with given keySpaceSize and plaintext.
 * We store the resulting cipher->keyset map in cipherTable.
 */
void forward(int keySpaceSize,
             unsigned char plaintext[2][2],
             unordered_map<bitset<16>, vector<vector<unsigned char>>> *cipherTable) {

    // find all key combinations going forward
    for (int i = 0; i < keySpaceSize; i++) {
        for (int j = 0; j < keySpaceSize; j++) {

            unsigned char currentCipher[2];
            unsigned char keys[2];
            keys[0] = static_cast<unsigned char>(i);
            keys[1] = static_cast<unsigned char>(j);

            // encrypt plaintext0 with 2 rounds
            Encrypter<0>::feistel(plaintext[0], currentCipher, keys, 2);

            bitset<8> c1(currentCipher[0]);
            bitset<8> c2(currentCipher[1]);

            bitset<16> index = Encrypter<0>::concat(c1, c2);

            // store the cipher->keyset pair in the cipherTable
            vector<unsigned char> tempKeys = {keys[0], keys[1]};
            if ((*cipherTable).find(index) == (*cipherTable).end()) {
                vector<vector<unsigned char>> indexKeys = {tempKeys};
                (*cipherTable)[index] = indexKeys;
            }
            else {
                // handle collisions between ciphers
                vector<vector<unsigned char>> indexKeys = (*cipherTable)[index];
                indexKeys.push_back(tempKeys);
                (*cipherTable)[index] = indexKeys;
            }
        }
    }
}

/**
 * backward-decrypt 2 rounds of inverseFeistel with given keySpaceSize and cipher.
 * We store the resulting array of keysets in keys.
 */
int backward(int keySpaceSize,
             unsigned char cipher[2][2],
             unordered_map<bitset<16>, vector<vector<unsigned char>>> *cipherTable,
             unsigned char keys[][4]) {
    int x = 0;

    // find all key combinations going backwards
    for (int i = 0; i < keySpaceSize; i++) {
        for (int j = 0; j < keySpaceSize; j++) {

            unsigned char currentPlaintext[2];
            unsigned char tempKeys[2];
            tempKeys[0] = i;
            tempKeys[1] = j;

            // decrypt cipher0 with 2 rounds
            Encrypter<0>::inverseFeistel(cipher[0], currentPlaintext, tempKeys, 2);

            bitset<8> c1(currentPlaintext[0]);
            bitset<8> c2(currentPlaintext[1]);

            bitset<16> index = Encrypter<0>::concat(c1, c2);

            // do the currentPlaintext's exist in ciphertable?
            if ((*cipherTable).find(index) != (*cipherTable).end()) {

                // store all keysets in cipherTable entry
                for (int k = 0; k < (*cipherTable)[index].size(); k++) {

                    keys[x][0] = (*cipherTable)[index][k][0];
                    keys[x][1] = (*cipherTable)[index][k][1];
                    keys[x][2] = tempKeys[0];
                    keys[x][3] = tempKeys[1];
                    x++;
                }
            }
        }
    }

    // return number of candidate keysets
    return x;
}

/**
 * Test if the ciphers stored in cipherTable can actually be decrypted into plaintext using 2 inverseFeistel rounds.
 */
void testForward(unsigned char plaintext[2][2],
                 unordered_map<bitset<16>, vector<vector<unsigned char>>> *cipherTable) {

    for (auto keyValue : *cipherTable) {

        tuple<bitset<8>, bitset<8>> temp = Encrypter<0>::split(keyValue.first);

        bitset<8> b1 = get<0>(temp);
        bitset<8> b2 = get<1>(temp);

        unsigned char currentCipher[2];
        currentCipher[0] = static_cast<unsigned char>(b1.to_ulong());
        currentCipher[1] = static_cast<unsigned char>(b2.to_ulong());

        vector<vector<unsigned char>> tempKeys = keyValue.second;

        for (int i = 0; i < tempKeys.size(); i++) {

            unsigned char cipherKeys[2];
            cipherKeys[0] = tempKeys[i][0];
            cipherKeys[1] = tempKeys[i][1];

            unsigned char plaintextResult[2];
            Encrypter<0>::inverseFeistel(currentCipher, plaintextResult, cipherKeys, 2);

            if (plaintextResult[0] != plaintext[0][0]
                || plaintextResult[1] != plaintext[0][1]) {
                // we should never reach this point
                throw new exception();
            }
        }
    }
}

/**
 * meet-in-the-middle attack on 4 rounds of feistel
 * stores the resulting keysets in returnKeys
 */
template<size_t T>
void Encrypter<T>::mitm(unsigned char plaintext[2][2],
                        unsigned char cipher[2][2],
                        unsigned char returnKeys[2][4]) {

    int keySpace = pow(2, 8);

    // map from cipher to keyset
    unordered_map<bitset<16>, vector<vector<unsigned char>>> cipherTable;
    unsigned char keys[keySpace * keySpace][4];

    forward(keySpace, plaintext, &cipherTable);

    testForward(plaintext, &cipherTable);

    // number of candidate keys to iterate over after going backward to confirm a match
    int x = backward(keySpace, cipher, &cipherTable, keys);

    // number of found keysets - to get down to 1 keyset we would need 1 more cipher/plaintext pair
    // with two cipher/plaintext pairs we find 2 candidate keysets
    int keySets = 0;

    // find the cipher permutations of keys in returnKeys using plaintext[1]
    // check if a cipher exists which match a cipher in resultTable (going backwards)
    for (int i = 0; i < x; i++) {

        unsigned char cipherResult[2][2];

        Encrypter<T>::feistel(plaintext[0], cipherResult[0], keys[i], 4);
        Encrypter<T>::feistel(plaintext[1], cipherResult[1], keys[i], 4);

        // can this keypair encrypt plaintext0 to cipher0?
        if (cipherResult[1][0] == cipher[1][0]
            && cipherResult[1][1] == cipher[1][1]) {

            // can this keypair also encrypt plaintext1 to cipher1?
            if (cipherResult[0][0] == cipher[0][0]
                && cipherResult[0][1] == cipher[0][1]) {

                returnKeys[keySets][0] = keys[i][0];
                returnKeys[keySets][1] = keys[i][1];
                returnKeys[keySets][2] = keys[i][2];
                returnKeys[keySets][3] = keys[i][3];
                keySets++;
            }
        }
    }
}