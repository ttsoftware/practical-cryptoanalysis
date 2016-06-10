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

template<size_t T> class Encrypter {

public:
    static mutex coutMutex;

    static bitset<T> bruteforce(bitset<T> plainText,
                                bitset<T> cipherText,
                                time_t maxSeconds,
                                uint64_t keySpaceStart,
                                uint64_t keySpaceEnd);

    static bitset<T> encrypt(bitset<T> key, bitset<T> plaintext);

    static bitset<28> md5Redux(bitset<T> input);

    static bitset<28> reduceSize(bitset<T> input);

    static void chain(bitset<T> input,
                      unordered_map<bitset<T>, bitset<T>> *coveredBits);

    static void writeToFile(unordered_map<bitset<T>, bitset<T>> *coveredBits, string path);

    static unordered_map<bitset<T>, bitset<T>> loadFromFile(string path);

private:
    static bitset<T> increment(bitset<T> input);
};

// We need to include at compile-time, otherwise <T> will not be available at link-time
#include "Encrypter.cpp"

#endif //EXERCISES_AND_PROJECTS_ENCRYPTER_H
