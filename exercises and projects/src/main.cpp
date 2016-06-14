#include <random>
#include "lib/Encrypter.h"

using namespace std;

/**
 * Computes a rainbow table from the given input and stores end and start point in the rainbow table given.
 *
 * @challenge: The selected challenge, u.
 * @chainCount: The number of chains to generate.
 * @maxRand: the maximum value for each input. Based on the size of the key.
 * @chainLength: The length of each chain.
 * @rainbowTable: The map to store the end point, start point pair.
 */
void computeRainbowTable(bitset<28> challenge,
                        int chainCount,
                        int maxRand,
                        int chainLength,
                        unordered_map<bitset<28>, bitset<28>> *rainbowTable) {

    //random generator
    default_random_engine generator;
    uniform_int_distribution<int> distribution(0,maxRand);

    //Count of duplicate keys
    int duplicates = 0;

    for (int i = 0; i < chainCount; i++) {
        //Get new random
        int r = distribution(generator);

        //Convert random to input bitset and compute chian
        bitset<28> input((unsigned long long int) r);
        bitset<28> result = Encrypter<28>::chain(input, challenge, 1, chainLength);

        //Check that the resulting output does not exist in the chain
        auto it = (*rainbowTable).find(result);

        //Already in the set - compute new rand()
        if(it != (*rainbowTable).end()){
            i--;
            duplicates++;
            cout << "Key already in the set: " << duplicates << " in chain " <<  i << endl;
            //Continue - redo the chain with a new random value
            continue;
        }

        //Store result in the rainbow table
        (*rainbowTable)[result] = input;
    }
}
/**
 * Overall function for setting default values, building the table and storing to file.
 *
 * @challenge: Selected challenge.
 * @filename: Full path to store table to.
 */
void buildRainbowTable(bitset<28> challenge, string filename) {

    //Init table constrains
    int maxRand = pow(2, 28);
    int maxChains = pow(2, 18);
    int chainLength = pow(2,10);

    //Init map
    unordered_map<bitset<28>, bitset<28>> rainbowTable;

    //Compute map
    computeRainbowTable(challenge, maxChains, maxRand, chainLength, &rainbowTable);

    //Write to file
    Encrypter<28>::writeToFile(&rainbowTable, filename);
}

/**
 * Tests the computed rainbow table and outputs the number of hits pr. 100 tries.
 *
 * @filename: The path to the stored rainbow table.
 * @challenge: The challenge that the rainbow table is based on.
 */
void testTable(string filename, bitset<28> challenge){
    int count = 0;
    int max = 100;

    default_random_engine generator;
    uniform_int_distribution<int> distribution(0,pow(2, 28));
    int maxRand = pow(2,28);

    for(int i = 0; i < max; i++){
//        int r = distribution(generator);
        int r = rand() % maxRand;

        bitset<28> key((unsigned long long int) r);

        unordered_map<bitset<28>, bitset<28>> map = Encrypter<28>::loadFromFile(filename);
        count = Encrypter<28>::breakKey(&map, challenge, key)
                ? count + 1
                : count;

        cout << i << endl;
    }

    cout << "Total matches on "<< max <<" runs: " << count << endl;
}

int main() {

    //Hardcoded challenge.
    bitset<28> challenge("1010101010101010101010101010");

    string filename = "/projects/rainbow_table_challenge_multi2.txt";

//    buildRainbowTable(challenge, filename);

    testTable(filename, challenge);

    return 0;
}