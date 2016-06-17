#include "Encrypter.h"

string Encrypter::decrypt(unsigned char cipher[], int length, unsigned char key[]){

    unsigned char output[length];
    AES_KEY decryptKey;

    AES_set_decrypt_key(key, 128, &decryptKey);

    for(int i = 0; i < length; i+= 16){
        AES_ecb_encrypt(cipher+i, output+i, &decryptKey, AES_DECRYPT);
    }

    string result((char *)output);
    return result;
}

int Encrypter::getTime(){
    struct tm date = {0};
    date.tm_year = 114;
    date.tm_hour = 0;
    date.tm_min = 0;
    date.tm_mon = 5;
    date.tm_sec = 0;
    date.tm_mday = 22;

    time_t time = timegm(&date);

    return time;
}

void Encrypter::getKey(int time, unsigned char *output){

    unsigned int mod = pow(2,31);

    unsigned int temp = time;
    //run over each byte in the key
    for(int i = 0; i < 16; i++){
        temp = (temp * 1103515245 + 12345) % mod;

        uint8_t key = temp;

        output[i] = key;
    }
}

unsigned char * Encrypter::readFile(string path){
    ifstream input(path, ios::binary);

    if (input) {
        // get length of file:
        input.seekg(0, input.end);
        int length = input.tellg();
        input.seekg(0, input.beg);

        unsigned char * out = new unsigned char[length];

        cout << "Reading " << length << " characters... " << endl;
        // read data as a block:
        input.read((char *)out, length);

        if (input)
            cout << "all characters read successfully." << endl;

        input.close();

        return out;
    }

    return NULL;
}