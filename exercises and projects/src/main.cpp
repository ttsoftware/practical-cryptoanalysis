#include "lib/Encrypter.h"

using namespace std;

void threadRainbowTable(bitset<28> challenge,
                        int chainCount,
                        int maxRand,
                        unordered_map<bitset<28>, bitset<28>> *rainbowTable) {

    int chainLength = pow(2, 10);

    for (int i = 0; i < chainCount; i++) {
        int r = rand() % maxRand;

        bitset<28> input((unsigned long long int) r);

        (*rainbowTable)[ Encrypter<28>::chain(input, challenge, 1, chainLength, false) ] = input;
    }
}

void buildRainbowTable(bitset<28> challenge, string filename) {

    int maxRand = pow(2, 28);
    int maxChains = pow(2, 10);

    unordered_map<bitset<28>, bitset<28>> rainbowTable;

    int t_chains = maxChains / 4;

//    unordered_map<bitset<28>, bitset<28>> t1_rainbowTable;
//    unordered_map<bitset<28>, bitset<28>> t2_rainbowTable;
//    unordered_map<bitset<28>, bitset<28>> t3_rainbowTable;
//    unordered_map<bitset<28>, bitset<28>> t4_rainbowTable;

    thread t1 = thread(threadRainbowTable, challenge, maxChains, maxRand, &rainbowTable);
//    thread t2 = thread(threadRainbowTable, challenge, t_chains, maxRand, &t2_rainbowTable);
//    thread t3 = thread(threadRainbowTable, challenge, t_chains, maxRand, &t3_rainbowTable);
//    thread t4 = thread(threadRainbowTable, challenge, t_chains, maxRand, &t4_rainbowTable);

    t1.join();
//    t2.join();
//    t3.join();
//    t4.join();

//    rainbowTable.insert(t1_rainbowTable.begin(), t1_rainbowTable.end());
//    rainbowTable.insert(t2_rainbowTable.begin(), t2_rainbowTable.end());
//    rainbowTable.insert(t3_rainbowTable.begin(), t3_rainbowTable.end());
//    rainbowTable.insert(t4_rainbowTable.begin(), t4_rainbowTable.end());

    Encrypter<28>::writeToFile(&rainbowTable, filename);
}

int main() {

    bitset<28> challenge("1010101010101010101010101010");
//Key that generates the chain
//    bitset<28>       key("0110111110010111010010110010");

    //key that should be in the chain generated above
    bitset<28>       key("0101000011111011001101110011");

    bitset<28>       test("1110101110110101111011110111");


    string filename = "/projects/rainbow_table_challenge_multi.txt";

    //TEST OF MD5

//    bitset<56> concat = Encrypter<28>::concat(key, challenge);
//
//    cout << "Concat: " << endl;
//    cout << key << challenge << endl;
//    cout << concat << endl;
//
//    cout << Encrypter<56>::reduceSize(concat) << endl;


//    cout << "Test encrypt" << endl;
//    cout << Encrypter<28>::encrypt(test, challenge) << endl;
//    cout << "1001010000100101101000010100" << endl;


    unordered_map<bitset<28>, bitset<28>> map = Encrypter<28>::loadFromFile(filename);
    Encrypter<28>::breakKey(&map, challenge, key);

//    buildRainbowTable(challenge, filename);

    // unordered_map<bitset<28>, bitset<28>> map = Encrypter<28>::loadFromFile("rainbow_table_challenge_multi.txt");



    /*if (map1.size() != map2.size()) {
        throw exception();
    }*/

    return 0;
}