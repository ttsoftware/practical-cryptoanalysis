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

    static string decrypt(unsigned char cipher[], int length, unsigned char key[]);

    static int getTime();

    static void getKey(int time, unsigned char *output);

    static unsigned char * readFile(string path);
};

// We need to include at compile-time, otherwise <T> will not be available at link-time
#include "Encrypter.cpp"

#endif //EXERCISES_AND_PROJECTS_ENCRYPTER_H
