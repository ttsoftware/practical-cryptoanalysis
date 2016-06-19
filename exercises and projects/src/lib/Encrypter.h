#ifndef EXERCISES_AND_PROJECTS_ENCRYPTER_H
#define EXERCISES_AND_PROJECTS_ENCRYPTER_H

#include <iostream>
#include <fstream>
#include <bitset>
#include <openssl/AES.h>
#include <unordered_map>
#include <cmath>
#include <cstring>
#include <vector>
#include <time.h>

using namespace std;

class Encrypter {

public:

    /**
     * Decrypts the given cipher array of the given length by using the inputted key.
     * Returns the result as a string.
     *
     * @cipher: The cipher to decrypt.
     * @length: The length of the cipher.
     * @key: The key byte.
     */
    static string decrypt(unsigned char cipher[], int length, unsigned char key[]);

    /**
     * Retrieves the time epoch to since 22 june 2014.
     */
    static int getTime();

    /**
     * Converts the timestamp into the byte array by applying
     * the random function.
     * @time: Seconds since epoch.
     * @output: A byte array.
     */
    static void getKey(int time, unsigned char *output);

    /**
     * Reads in the file and return a pointer to the byte array.
     * @path: The full path to the file.
     */
    static unsigned char * readFile(string path);
};

// We need to include at compile-time, otherwise <T> will not be available at link-time
#include "Encrypter.cpp"

#endif //EXERCISES_AND_PROJECTS_ENCRYPTER_H
