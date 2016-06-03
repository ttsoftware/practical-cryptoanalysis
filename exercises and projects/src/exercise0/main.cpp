#include <iostream>
#include <bitset>
#include "encrypt.h"

using namespace std;

template <size_t N>
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

int main() {
    bitset<128> realKey(1);
    realKey <<= 127;

    bitset<128> plainText(20000000);
    bitset<128> cipherText = encrypt(realKey, plainText);

    bitset<128> incKey(0);
    bitset<128> tempCipher;

    int i = 0;
    while (i != 1000000000) {

        tempCipher = encrypt(incKey, plainText);

        if (tempCipher == cipherText) {
            break;
        }

        incKey = increment(incKey);
        i++;
    }

    // We could to 10^9 in ~2 minutes - so we estimate 30*10^9 iterations in an hour

    cout << incKey << endl;

    return 0;
}