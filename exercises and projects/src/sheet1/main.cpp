#include "../lib/Encrypter.h"

using namespace std;

int main() {

    unordered_map<bitset<20>, int> coveredBits;

    int maxRand = pow(2, 20);
    int maxChains = pow(2, 16);

    int md5Graph[maxChains];

    for (int i = 0; i < maxChains; i++) {
        int r = rand() % maxRand;

        bitset<20> input((unsigned long long int) r);
        Encrypter<20>::chain(input, &coveredBits);

        md5Graph[i] = coveredBits.size();
    }

    Encrypter<20>::writeToFile((int *) &md5Graph, maxChains, "md5_graph.txt");
    Encrypter<20>::writeToFile(&coveredBits, "rainbow_table.txt");

    unordered_map<bitset<20>, int> map = Encrypter<20>::loadFromFile("rainbow_table.txt");

    if (coveredBits.size() != map.size()) {
        throw exception();
    }

    return 0;
}