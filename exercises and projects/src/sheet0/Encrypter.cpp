#include "Encrypter.h"

template<size_t T>
mutex Encrypter<T>::coutMutex;

template<size_t T>
bitset<T> Encrypter<T>::encrypt(bitset<T> key,
                                bitset<T> plaintext) {
    return key ^ plaintext;
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