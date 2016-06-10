#include "lib/Encrypter.h"

using namespace std;

template <size_t T>
void breakKey(unordered_map<bitset<T>, bitset<T>> * map, bitset<T> challenge, bitset<T> secret){
    bitset<T> cipher = Encrypter<T>::encrypt(secret, challenge);

    bitset<T> result = Encrypter<T>::hax(cipher,map);

    cout << "Result:" << endl;
    cout << result << endl;
    cout << "Actual:" << endl;
    cout << secret << endl;
}

void threadRainbowTable(int chainCount, int maxRand, unordered_map<bitset<28>, bitset<28>> *rainbowTable) {

    for (int i = 0; i < chainCount; i++) {
        int r = rand() % maxRand;

        bitset<28> input((unsigned long long int) r);
        Encrypter<28>::chain(input, rainbowTable);
    }
}

int main() {

    unordered_map<bitset<28>, bitset<28>> rainbowTable;

    int maxRand = pow(2, 28);
    int maxChains = pow(2, 18);

    int t_chains = maxChains / 4;

    unordered_map<bitset<28>, bitset<28>> t1_rainbowTable;
    unordered_map<bitset<28>, bitset<28>> t2_rainbowTable;
    unordered_map<bitset<28>, bitset<28>> t3_rainbowTable;
    unordered_map<bitset<28>, bitset<28>> t4_rainbowTable;

    /*
    thread t1 = thread(threadRainbowTable, t_chains, maxRand, &t1_rainbowTable);
    thread t2 = thread(threadRainbowTable, t_chains, maxRand, &t2_rainbowTable);
    thread t3 = thread(threadRainbowTable, t_chains, maxRand, &t3_rainbowTable);
    thread t4 = thread(threadRainbowTable, t_chains, maxRand, &t4_rainbowTable);

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    rainbowTable.insert(t1_rainbowTable.begin(), t1_rainbowTable.end());
    rainbowTable.insert(t2_rainbowTable.begin(), t2_rainbowTable.end());
    rainbowTable.insert(t3_rainbowTable.begin(), t3_rainbowTable.end());
    rainbowTable.insert(t4_rainbowTable.begin(), t4_rainbowTable.end());

    Encrypter<28>::writeToFile(&rainbowTable, "rainbow_table_multi.txt");
    */

    unordered_map<bitset<28>, bitset<28>> map1 = Encrypter<28>::loadFromFile("/projects/rainbow_table.txt");
    unordered_map<bitset<28>, bitset<28>> map2 = Encrypter<28>::loadFromFile("rainbow_table_multi.txt");

    /*if (map1.size() != map2.size()) {
        throw exception();
    }*/

    return 0;
}