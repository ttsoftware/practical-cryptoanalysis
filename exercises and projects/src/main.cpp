#include <random>
#include "lib/Encrypter.h"

using namespace std;


int main() {

    unsigned char key[16];
    unsigned char *cipher;

    string path("/projects/ciphertext_project3.bin");

    cipher = Encrypter::readFile(path);

    //seconds * minutes * hours * days (22-28 including both days)
    int possibleKeys = 60 * 60 * 24 * 7;

    int time = Encrypter::getTime();

    for(int i = 0; i < possibleKeys; i++){
        int curTime = time + i;
        Encrypter::getKey(curTime, (unsigned char *)&key);

        string decrypted = Encrypter::decrypt(cipher, 384, key);

//        cout << decrypted << endl;
//        cout << endl;

        size_t found = decrypted.find("Snowden");

        if (found!=string::npos){
            //Found
            cout << "Timestamp found: " << curTime << endl;
            cout << decrypted << endl;
            break;
        }
        cout << i << ": found: Next try..." << endl;
    }

    //We need a char input for the key.

    //This works
//    printf("Plain: [%s]\n", &input);

//    for(int i = 0; i < 8; i++){
//        cout << cipher[i] << endl;
//    }

//    unsigned char out[8];
//    Encrypter<8>::convertKey(key, (unsigned char *)&out);
//    bitset<56> res = Encrypter<7>::toBitset((unsigned char *)&out);

//    cout << key << endl;
//    cout << res << endl;

    return 0;
}