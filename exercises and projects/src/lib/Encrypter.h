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

using namespace std;

template<size_t T>
class Encrypter {

public:
    static unsigned char *mitm(unsigned char *plaintext,
                               unsigned char *cipher);

    static void feistel(unsigned char *plaintext,
                        unsigned char *cipher,
                        unsigned char *key,
                        int rounds);

private:
    /**
     * Concats two 28 bit bitsets into a 56 bitset. InputA will be the lowest 28 bits.
     */
    static bitset<16> concat(bitset<8> inputA, bitset<8> inputB);
};

// We need to include at compile-time, otherwise <T> will not be available at link-time
#include "Encrypter.cpp"

#endif //EXERCISES_AND_PROJECTS_ENCRYPTER_H
