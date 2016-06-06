#include "../lib/Encrypter.h"

using namespace std;

int main() {

    // unordered_map<bitset<20>, bitset<20>> hitler;
    unordered_map<bitset<20>, int> coveredBits;

    int maxRand = pow(2, 20);
    int maxChains = pow(2, 16);

    for (int i = 0; i < maxChains; i++) {
        int r = rand() % maxRand;

        bitset<20> input((unsigned long long int) r);

        bitset<20>* chain = Encrypter<20>::chain(input, &coveredBits);

        // hitler[chain[0]] = chain[255];
    }

    return 0;
}