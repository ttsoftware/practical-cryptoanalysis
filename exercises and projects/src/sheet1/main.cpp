#include "../lib/Encrypter.h"

using namespace std;

int main() {

    unordered_map<bitset<20>, int> coveredBits;

    int maxRand = pow(2, 20);
    int maxChains = pow(2, 4);

    for (int i = 0; i < maxChains; i++) {
        int r = rand() % maxRand;

        bitset<20> input((unsigned long long int) r);
        bitset<20>* chain = Encrypter<20>::chain(input, &coveredBits);
    }

    cout << "size: " << coveredBits.size() << endl;

    Encrypter<20>::writeToFile(&coveredBits, "/projects/rainbow_table.txt");
    unordered_map<bitset<20>, int> map = Encrypter<20>::loadFromFile("/projects/rainbow_table.txt");

    cout << "size: " << map.size() << endl;

    return 0;
}