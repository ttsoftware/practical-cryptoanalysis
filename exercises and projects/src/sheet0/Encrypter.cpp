#include "Encrypter.h"

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
                                   uint64_t keySpaceEnd,
                                   uint64_t * count) {

    //Bitshift key space that we search.
    bitset<T> incKey = keySpaceStart == 0 ? bitset<T>(0) : bitset<T>(1);
    bitset<T> endKey(1);
    incKey <<= keySpaceStart;
    endKey <<= keySpaceEnd;
    bitset<T> tempCipher;

    // stop if we reach the end of keyspace
    while (time(NULL) <= maxSeconds && (incKey.count() != keySpaceEnd)) {
        //Encrypt with new key

        tempCipher = Encrypter<T>::encrypt(incKey, plainText);
        //Increment external counter
        (*count)++;

        //if result found, terminate
        if (tempCipher == cipherText) {
            cout << "Found cipher: " << cipherText << endl;
            cout << incKey << endl;
            break;
        }
        //Increment key
        incKey = Encrypter<T>::increment(incKey);
    }

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