#include "Encrypter.h"

template<size_t T>
bitset<T> Encrypter<T>::increment(bitset<T> input) {
    for (size_t i = 0; i < T; ++i) {
        // There will be no carry
        if (input[i] == 0) {
            input[i] = 1;
            break;
        }
        // This entry was 1; set to zero and carry the 1
        input[i] = 0;
    }
    return input;
}

template<size_t T>
bitset<20> Encrypter<T>::reduceSize(bitset<T> input) {
    bitset<20> returnBits(0);
    for (size_t i = 0; i < 20; ++i) {
        returnBits[i] = input[i];
    }
    return returnBits;
}

template<size_t T>
unordered_map<bitset<T>, bitset<T>> Encrypter<T>::loadFromFile(string path) {
    string line;
    ifstream dump(path);

    unordered_map<bitset<T>, bitset<T>> map;

    if (dump.is_open()) {
        while (getline(dump, line)) {
            int del_position = line.find(":");
            string first = line.substr(0, del_position);
            string last = line.substr(del_position + 1, line.length());
            map[bitset<T>(first)] = bitset<T>(last);
        }
    }

    return map;
}

template<size_t T>
void Encrypter<T>::writeToFile(unordered_map<bitset<T>, bitset<T>> *coveredBits, string path) {
    ofstream dump;
    dump.open(path);

    for (auto it = coveredBits->begin(); it != coveredBits->end(); ++it) {
        dump << it->first << ":" << it->second << std::endl;
    }

    dump.close();
}