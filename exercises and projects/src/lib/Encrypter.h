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

class Encrypter {

public:

    static string decrypt(unsigned char cipher[], int length, unsigned char key[]);

    static int getTime();

    static void getKey(int time, unsigned char *output);
};

// We need to include at compile-time, otherwise <T> will not be available at link-time
#include "Encrypter.cpp"

#endif //EXERCISES_AND_PROJECTS_ENCRYPTER_H
