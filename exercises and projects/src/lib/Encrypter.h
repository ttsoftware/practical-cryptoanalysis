#ifndef EXERCISES_AND_PROJECTS_ENCRYPTER_H
#define EXERCISES_AND_PROJECTS_ENCRYPTER_H

#include <iostream>
#include <fstream>
#include <bitset>
#include <thread>
#include <mutex>
#include <openssl/md5.h>
#include <openssl/DES.h>
#include <unordered_map>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

template<size_t T> class Encrypter {

public:

    /**
     * Test all they keys in the keyspace by encrypting forward and stores the result in the given map.
     * @plaintext: The plaintext to encrypt.
     * @map: The map to store the output and key-mapping in.
     */
    static void testKeysForward(unsigned char *plaintext, unordered_map<bitset<64>, vector<bitset<20>>> *map);


    /**
     * Test all the keys in the key space by decrypting backwards.
     * Checks the output in the given map and stores the matching pair.
     * @cipher: The matching cipher for the given plaintext.
     * @map: The map containing the output and key-pair.
     * @pairs: The pairs of forward and backward keys.
     */
    static void testKeysBackward(unsigned char *cipher, unordered_map<bitset<64>, vector<bitset<20>>> *map, vector<tuple<bitset<20>,bitset<20>>> *pairs);

    /**
     * A wrapper function for the DES_ECB encryption. Converts the 20 bit key to a 7 byte char array.
     * @input: The input to be encrypted / decrypted.
     * @ouput: A output pointer.
     * @key: The 20 bit key.
     * @encrypt: true if encrypt, false if decrypt.
     */
    static void encrypt(unsigned char *input, unsigned char *output, bitset<20> key, bool encrypt);

    /**
     * Converts the key to a 7 byte char array.
     * @key: The 20 bit key.
     * @output: The output array.
     */
    static void convertKey(bitset<20> key, unsigned char * output);

    /**
     * Converts the given char array to a bitset.
     * @input: Expected size = T.
     */
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
