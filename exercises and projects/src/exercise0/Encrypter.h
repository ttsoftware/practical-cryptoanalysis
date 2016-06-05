//
// Created by troels on 6/5/16.
//

#ifndef EXERCISES_AND_PROJECTS_ENCRYPTER_H
#define EXERCISES_AND_PROJECTS_ENCRYPTER_H

#include <iostream>
#include <bitset>
#include <thread>
#include <mutex>

using namespace std;

template <size_t T> class Encrypter {

public:
    static mutex coutMutex;
    static bitset<T> bruteforce(bitset<T> plainText,
                                bitset<T> cipherText,
                                time_t maxSeconds,
                                uint64_t keySpaceStart,
                                uint64_t keySpaceEnd);

    static bitset<T> encrypt(bitset<T> key, bitset<T> plaintext);

private:
    static bitset<T> increment(bitset<T> input);
};

// We need to include at compile-time, otherwise <T> will not be available at link-time
#include "Encrypter.cpp"

#endif //EXERCISES_AND_PROJECTS_ENCRYPTER_H
