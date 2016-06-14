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

template<size_t T> class Encrypter {

public:

    /**
     * Computes a single chain based on the given input and returns the last element in the chain.
     *
     * @cipher: The given start point in the chain.
     * @challenge: The given challenge to build the rainbow table for.
     * @rainbowFunction: The rainbow function to be XOR'ed before applying the md5.
     * @chainLength: The length of the chain.
     *
     */
    static bitset<T> chain(bitset<T> cipher, bitset<T> challenge, int rainbowFunction, int chainLength);

    /**
     * Based on the input, the function computes a cipher from the challenge and the secret and then tries
     * to find the same key again by using the rainbow table given. Returns true if the original key is found.
     *
     * @map: The rainbow table.
     * @challenge: The challenge used for the rainbow table.
     * @secret: The given secret to find again.
     */
    static bool breakKey(unordered_map<bitset<T>, bitset<T>> *map, bitset<T> challenge, bitset<T> secret);

    /**
     * Writes the given table to the given path.
     */
    static void writeToFile(unordered_map<bitset<T>, bitset<T>> *map, string path);

    /**
     * Loads a table from the given path.
     */
    static unordered_map<bitset<T>, bitset<T>> loadFromFile(string path);

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

    /**
     * Concats the key and plaintext and encrypts the output. Reduces the output and returns 28 bits.
     */
    static bitset<T> encrypt(bitset<T> key, bitset<T> plaintext);

    /**
     * Encrypts the 56 bit iput and returns the encrypted and reduced 28 bit bitset.
     */
    static bitset<28> md5Redux(bitset<T> input);

    /**
     * Returns all the candidate keys for the given cipher.
     */
    static vector<bitset<T>> hax(bitset<T> cipher, bitset<T> challenge, unordered_map<bitset<T>, bitset<T> > *map);
};

// We need to include at compile-time, otherwise <T> will not be available at link-time
#include "Encrypter.cpp"

#endif //EXERCISES_AND_PROJECTS_ENCRYPTER_H
