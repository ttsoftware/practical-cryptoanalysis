#include "Encrypter.h"

template<size_t T>
mutex Encrypter<T>::coutMutex;

template<size_t T>
bitset<T> Encrypter<T>::encrypt(bitset<T> key,
                                bitset<T> plaintext) {
    return key ^ plaintext;
}

template<size_t T>
void Encrypter<T>::chain(bitset<T> input,
                         unordered_map<bitset<20>, int> *coveredBits,
                         int graphPosition,
                         int *md5Graph) {

    bitset<20> *chain = new bitset<20>[256];
    chain[0] = input;
    (*coveredBits)[chain[0]] = 1;
    md5Graph[graphPosition * 256] = coveredBits->size();

    for (int i = 1; i < 256; i++) {
        bitset<20> bitI (i);

        chain[i] = Encrypter<T>::md5Redux(chain[i - 1]);
        chain[i] ^= bitI;

        if ((*coveredBits)[chain[i]] == 0) {
            (*coveredBits)[chain[i]] = 1;
        }
        else {
            (*coveredBits)[chain[i]] += 1;
        }

        md5Graph[graphPosition * 256 + i] = coveredBits->size();
    }
}

template<size_t T>
bitset<20> Encrypter<T>::md5Redux(bitset<T> input) {

    bitset<20> reducedInput = Encrypter<T>::reduceSize(input);

    char inputChars[] = {};
    for (int i = 0; i < 20; i++) {
        inputChars[i] = reducedInput[i];
    }

    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char *) &inputChars, 20, (unsigned char *) &digest);

    bitset<8 * MD5_DIGEST_LENGTH> md5Bits;
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        unsigned char c = digest[i];
        for (int j = 7; j >= 0 && c; --j) {
            if (c & 0x01) {
                // if right-most bit is 1, we set the (8*i+j) bit to 1
                md5Bits.set(8 * i + j);
            }
            // shift c 1 to the right
            c >>= 1;
        }
    }

    return Encrypter<8 * MD5_DIGEST_LENGTH>::reduceSize(md5Bits);
}

template<size_t T>
bitset<T> Encrypter<T>::bruteforce(bitset<T> plainText,
                                   bitset<T> cipherText,
                                   time_t maxSeconds,
                                   uint64_t keySpaceStart,
                                   uint64_t keySpaceEnd) {

    thread::id tid = this_thread::get_id();

    cout << "Thread: " << tid << " : " << keySpaceStart << " - " << keySpaceEnd << endl;

    bitset<T> incKey(keySpaceStart);
    bitset<T> tempCipher;

    uint64_t cycleCount = 0;

    // stop if we reach the end of keyspace
    while (time(NULL) <= maxSeconds && incKey.count() < keySpaceEnd) {
        tempCipher = Encrypter<T>::encrypt(incKey, plainText);

        if (tempCipher == cipherText) {
            cout << incKey << endl;
            break;
        }

        incKey = Encrypter<T>::increment(incKey);
        cycleCount++;
    }

    coutMutex.lock();
    cout << "Thread: " << tid << " : " << cycleCount << " cycles" << endl;
    cout << "Thread: " << tid << " : " << incKey << " key" << endl;
    coutMutex.unlock();

    return incKey;
}

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
unordered_map<bitset<20>, int> Encrypter<T>::loadFromFile(string path) {
    string line;
    ifstream dump(path);

    unordered_map<bitset<20>, int> map;

    if (dump.is_open()) {
        while (getline(dump, line)) {
            int del_position = line.find(":");
            string first = line.substr(0, del_position);
            string last = line.substr(del_position + 1, line.length());
            bitset<20> bits = bitset<20>(first);
            map[bits] = stoi(last);
        }
    }

    return map;
}

template<size_t T>
void Encrypter<T>::writeToFile(unordered_map<bitset<20>, int> *coveredBits, string path) {
    ofstream dump;
    dump.open(path);

    for (auto it = coveredBits->begin(); it != coveredBits->end(); ++it) {
        dump << it->first << ":" << it->second << std::endl;
    }

    dump.close();
}

template<size_t T>
void Encrypter<T>::writeToFile(int *graph, int graphSize, string path) {
    ofstream dump;
    dump.open(path);

    for (int i = 0; i < graphSize; i++) {
        dump << graph[i] << endl;
    }

    dump.close();
}