#include <random>
#include "lib/Encrypter.h"

using namespace std;


int main() {

    unsigned char key[16];
    unsigned char *cipher;

    //Path to the file
    string path("/projects/ciphertext_project3.bin");

    //Read in the file in bytes
    cipher = Encrypter::readFile(path);

    //seconds * minutes * hours * days (22-28 including both days)
    int possibleKeys = 60 * 60 * 24 * 7;

    //Retrieve the starting timestamp for the time period to process
    int time = Encrypter::getTime();

    //Loop over all the possible time stamps
    for(int i = 0; i < possibleKeys; i++){
        //Increment the timestamp
        int curTime = time + i;

        //Apply the random function to the time
        Encrypter::getKey(curTime, (unsigned char *)&key);

        //Decrypt the string
        string decrypted = Encrypter::decrypt(cipher, 384, key);

        //Search for Mr. Snowden in the text
        size_t found = decrypted.find("Snowden");

        //Match if true
        if (found!=string::npos){
            cout << "Length: " << decrypted.length() << endl;
            //Found
            cout << "Timestamp found: " << curTime << endl;
            cout << decrypted << endl;
            break;
        }
        cout << i << ": found: Next try..." << endl;
    }

    return 0;
}