#include "lib/Encrypter.h"

using namespace std;

int main() {

    unordered_map<bitset<28>, bitset<28>> coveredBits;

    int maxRand = pow(2, 28);
    int maxChains = pow(2, 18);

    for (int i = 0; i < maxChains; i++) {
        int r = rand() % maxRand;

        bitset<28> input((unsigned long long int) r);
        Encrypter<28>::chain(input, &coveredBits);
    }

    Encrypter<28>::writeToFile(&coveredBits, "rainbow_table.txt");

    unordered_map<bitset<28>, bitset<28>> map = Encrypter<28>::loadFromFile("rainbow_table.txt");

    if (coveredBits.size() != map.size()) {
        throw exception();
    }

    return 0;
}