#include <random>
#include "lib/Encrypter.h"

using namespace std;


int main() {

    bitset<20>  key1("00000000000000000000");
    bitset<20>  key2("10101010101010101010");

    unsigned char input[] = "testtest";
    unsigned char temp[8];
    unsigned char cipher[8];

    //This works. Generates the cipher by applying two layers.
    Encrypter<20>::encrypt((unsigned char *) &input, (unsigned char *) &temp, key1, true);
    Encrypter<20>::encrypt((unsigned char *) &temp, (unsigned char *) &cipher, key2, true);

    //Test all keys in the keyspace moving forward
    unordered_map<bitset<64>, vector<bitset<20>>> map;
    Encrypter<20>::testKeysForward((unsigned char *) &input, &map);

    //Test all keys in the keyspace moving backward
    vector<tuple<bitset<20>,bitset<20>>> pairs;
    Encrypter<20>::testKeysBackward((unsigned char *) &cipher, &map, &pairs);

    return 0;
}