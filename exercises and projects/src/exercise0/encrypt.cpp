#include <thread>
#include "encrypt.h"

template<size_t N>
bitset<N> increment(bitset<N> input) {
    for (size_t i = 0; i < N; ++i) {
        if (input[i] == 0) {  // There will be no carry
            input[i] = 1;
            break;
        }
        input[i] = 0;  // This entry was 1; set to zero and carry the 1
    }
    return input;
}

bitset<128> encrypt(bitset<128> key, bitset<128> plaintext) {
    return key ^ plaintext;
}

bitset<128> bruteforce(bitset<128> plainText,
                       bitset<128> cipherText,
                       time_t maxSeconds,
                       uint64_t keySpaceStart,
                       uint64_t keySpaceEnd) {

    cout << "Thread: " << this_thread::get_id() << ":" << keySpaceStart * 8 << endl;

    bitset<128> incKey(keySpaceStart * 8);
    bitset<128> tempCipher;

    uint64_t cycleCount = 0;

    // stop if we reach the end of keyspace
    while (time(NULL) <= maxSeconds && (incKey.count() / 8) < keySpaceEnd) {
        tempCipher = encrypt(incKey, plainText);

        if (tempCipher == cipherText) {
            cout << incKey << endl;
            break;
        }

        incKey = increment(incKey);
        cycleCount++;
    }

    cout << "Thread: " << this_thread::get_id() << ":" << cycleCount << endl;
    cout << "Thread: " << this_thread::get_id() << ":" << incKey << endl;

    return incKey;
}