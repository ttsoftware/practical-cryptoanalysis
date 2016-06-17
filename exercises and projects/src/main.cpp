#include <random>
#include "lib/Encrypter.h"

using namespace std;


int main() {

    bitset<20>  key1("00000000000000000000");
    bitset<20>  key2("10101010101010101010");

    unsigned char input[] = "testtest";
    unsigned char temp[8];
    unsigned char cipher[8];

    //We need a char input for the key.

    //This works
    Encrypter<20>::encrypt((unsigned char *) &input, (unsigned char *) &temp, key1, true);
    Encrypter<20>::encrypt((unsigned char *) &temp, (unsigned char *) &cipher, key2, true);

//    printf("Plain: [%s]\n", &input);

//    for(int i = 0; i < 8; i++){
//        cout << cipher[i] << endl;
//    }

//    unsigned char out[8];
//    Encrypter<8>::convertKey(key, (unsigned char *)&out);
//    bitset<56> res = Encrypter<7>::toBitset((unsigned char *)&out);

//    cout << key << endl;
//    cout << res << endl;

    unordered_map<bitset<64>, vector<bitset<20>>> map;
    Encrypter<20>::testKeysForward((unsigned char *) &input, &map);

    vector<tuple<bitset<20>,bitset<20>>> pairs;
    Encrypter<20>::testKeysBackward((unsigned char *) &cipher, &map, &pairs);

    return 0;
}