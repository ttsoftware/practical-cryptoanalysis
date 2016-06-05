#include "Encrypter.h"

template<size_t T>
bitset<T> Encrypter<T>::increment(bitset<T> input) {
    for (size_t i = 0; i < T; ++i) {
        if (input[i] == 0) {  // There will be no carry
            input[i] = 1;
            break;
        }
        input[i] = 0;  // This entry was 1; set to zero and carry the 1
    }
    return input;
}

template <size_t T>
bitset<T> Encrypter<T>::encrypt(bitset<T> key, bitset<T> plaintext) {
    return key ^ plaintext;
}

template <size_t T>
bitset<T> Encrypter<T>::bruteforce(bitset<T> plainText,
                                bitset<T> cipherText,
                                time_t maxSeconds,
                                uint64_t keySpaceStart,
                                uint64_t keySpaceEnd) {

    cout << "Thread: " << this_thread::get_id() << ":" << keySpaceStart << " - " << keySpaceEnd << endl;

    bitset<128> incKey(keySpaceStart);
    bitset<128> tempCipher;

    uint64_t cycleCount = 0;

    // stop if we reach the end of keyspace
    while (time(NULL) <= maxSeconds && incKey.count()< keySpaceEnd) {
        tempCipher = encrypt(incKey, plainText);

        if (tempCipher == cipherText) {
            cout << incKey << endl;
            break;
        }

        incKey = Encrypter<T>::increment(incKey);
        cycleCount++;
    }

    cout << "Thread: " << this_thread::get_id() << ":" << cycleCount << endl;
    cout << "Thread: " << this_thread::get_id() << ":" << incKey << endl;

    return incKey;
}