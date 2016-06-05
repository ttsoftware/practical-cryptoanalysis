#ifndef EXERCISES_AND_PROJECTS_ENCRYPT_H
#define EXERCISES_AND_PROJECTS_ENCRYPT_H

#include <iostream>
#include <bitset>

using namespace std;

bitset<128> encrypt(bitset<128> key, bitset<128> plaintext);

bitset<128> bruteforce(bitset<128> plainText,
                       bitset<128> cipherText,
                       time_t maxSeconds,
                       uint64_t keySpaceStart,
                       uint64_t keySpaceEnd);

#endif //EXERCISES_AND_PROJECTS_ENCRYPT_H
