#include "Encrypter.h"

template<size_t T>
mutex Encrypter<T>::coutMutex;

template<size_t T>
bitset<T> Encrypter<T>::encrypt(bitset<T> key,
                                bitset<T> plaintext) {
    return key ^ plaintext;
}

template<size_t T>
bitset<20> *Encrypter<T>::chain(bitset<T> input, unordered_map<bitset<20>, int>* coveredBits) {

    bitset<20>* chain = new bitset<20>[256];
    chain[0] = input;
    (*coveredBits)[chain[0]] = 1;

    for (int i = 1; i < 256; i++) {
        chain[i] = Encrypter<T>::md5Redux(chain[i - 1]);

        if ((*coveredBits)[chain[i]] == NULL) {
            (*coveredBits)[chain[i]] = 1;
        }
        else {
            (*coveredBits)[chain[i]] += 1;
        }
    }

    return chain;
}

template<size_t T>
bitset<20> Encrypter<T>::md5Redux(bitset<T> input) {

    unsigned char digest[20];

    bitset<20> reducedInput = Encrypter<T>::reduceSize(input);
    string stringInput = reducedInput.to_string();

    MD5((unsigned char *) &stringInput, stringInput.length(), (unsigned char *) &digest);

    bitset<20> p;
    p |= bitset<20>(digest[0]);
    p <<= 8;
    p |= bitset<20>(digest[1]);
    p <<= 4;
    bitset<20> lastbits(digest[2]);
    lastbits >>= 4; // shift the 4 least significant bits out of this world
    p |= lastbits;

    // cout << p << endl;

    return p;
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
    bitset<20> returnBits;
    for (size_t i = 0; i < 20; ++i) {
        returnBits[20 - i] = input[T - i];
    }
    return returnBits;
}