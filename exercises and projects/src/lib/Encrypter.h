#ifndef EXERCISES_AND_PROJECTS_ENCRYPTER_H
#define EXERCISES_AND_PROJECTS_ENCRYPTER_H

#include <iostream>
#include <fstream>
#include <bitset>
#include <thread>
#include <mutex>
#include <openssl/md5.h>
#include <unordered_map>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

template<size_t T>
class Encrypter {

public:
    static void mitm(unsigned char plaintext[2][2],
                     unsigned char cipher[2][2],
                     unsigned char returnKeys[2][4]);

    static void feistel(unsigned char *plaintext,
                        unsigned char *cipher,
                        unsigned char *key,
                        int rounds);

    static void inverseFeistel(unsigned char *plaintext,
                               unsigned char *cipher,
                               unsigned char *key,
                               int rounds);

    static bitset<16> concat(bitset<8> inputA, bitset<8> inputB);

    static tuple<bitset<8>, bitset<8>> split(bitset<16> input);
};

// We need to include at compile-time, otherwise <T> will not be available at link-time
#include "Encrypter.cpp"

#endif //EXERCISES_AND_PROJECTS_ENCRYPTER_H
