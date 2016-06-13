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

template <size_t T> class Encrypter {

public:
    static void writeToFile(unordered_map<bitset<T>, bitset<T>> *coveredBits, string path);

    static unordered_map<bitset<T>, bitset<T>> loadFromFile(string path);

private:
    static bitset<20> reduceSize(bitset<T> input);

    static bitset<T> increment(bitset<T> input);
};

// We need to include at compile-time, otherwise <T> will not be available at link-time
#include "Encrypter.cpp"

#endif //EXERCISES_AND_PROJECTS_ENCRYPTER_H
