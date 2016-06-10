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
    static bitset<T> encrypt(bitset<T> key, bitset<T> plaintext);

    static bitset<28> md5Redux(bitset<T> input);

    static bitset<T> rainbowLookup(bitset<T> cipher, int rainbowFunction, int chainLength);

    static bitset<T> hax(bitset<T> cipher, unordered_map<bitset<T>, bitset<T> > *map);

    static void breakKey(unordered_map<bitset<T>, bitset<T>> *map, bitset<T> challenge, bitset<T> secret);

    static void chain(bitset<T> input,
                      bitset<T> challenge,
                      unordered_map<bitset<T>, bitset<T>> *rainbowTable);

    static void writeToFile(unordered_map<bitset<T>, bitset<T>> *map, string path);

    static unordered_map<bitset<T>, bitset<T>> loadFromFile(string path);

    static bitset<T> increment(bitset<T> input);

    static bitset<28> reduceSize(bitset<T> input);

    static bitset<56> concat(bitset<28> inputA, bitset<28> inputB);

private:
    static bitset<T> chainLookup(bitset<T> start, int rainbowFunction, int chainLength);
};

// We need to include at compile-time, otherwise <T> will not be available at link-time
#include "Encrypter.cpp"

#endif //EXERCISES_AND_PROJECTS_ENCRYPTER_H
