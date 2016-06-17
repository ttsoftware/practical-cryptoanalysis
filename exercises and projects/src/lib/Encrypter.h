#ifndef EXERCISES_AND_PROJECTS_ENCRYPTER_H
#define EXERCISES_AND_PROJECTS_ENCRYPTER_H

#include <iostream>
#include <fstream>
#include <bitset>
#include <thread>
#include <mutex>
#include <openssl/AES.h>
#include <unordered_map>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

template<size_t T> class Encrypter {

public:

    static string decrypt(unsigned char cipher[], int length, unsigned char key[]);

    static int getTime();

    static void getKey(int time, unsigned char *output);

    static void testKeysForward(unsigned char *plaintext, unordered_map<bitset<64>, vector<bitset<20>>> *map);

    static void testKeysBackward(unsigned char *cipher, unordered_map<bitset<64>, vector<bitset<20>>> *map, vector<tuple<bitset<20>,bitset<20>>> *pairs);

    static void encrypt(unsigned char *input, unsigned char *output, bitset<20> key, bool encrypt);

    static void convertKey(bitset<20> key, unsigned char * output);

    static bitset<T * 8> toBitset(unsigned char * input);

    /**
     * Increments the given bitset.
     */
    static bitset<T> increment(bitset<T> input);

    /**
     * Reduces the size of the given bitset to 28.
     */
    static bitset<28> reduceSize(bitset<T> input);


    /**
     * Concats two 28 bit bitsets into a 56 bitset. InputA will be the lowest 28 bits.
     */
    static bitset<56> concat(bitset<28> inputA, bitset<28> inputB);


};

// We need to include at compile-time, otherwise <T> will not be available at link-time
#include "Encrypter.cpp"

#endif //EXERCISES_AND_PROJECTS_ENCRYPTER_H
