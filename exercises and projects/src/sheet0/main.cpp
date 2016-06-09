#include "Encrypter.h"
#include <cmath>

using namespace std;

const size_t keySize = 128;

int main() {

    bitset<keySize> realKey(1);
    realKey <<= keySize - 1;

    bitset<keySize> plainText(1000000000);
    bitset<keySize> cipherText = Encrypter<keySize>::encrypt(realKey, plainText);

    cout << plainText << endl;
    cout << cipherText << endl;

    // should terminate after 1 hour
    time_t maxSeconds = time(NULL) + 60 * 60;

    uint64_t keySpaceStart0 = 0;
    uint64_t keySpaceEnd0 = 31;

    uint64_t keySpaceStart1 = 31;
    uint64_t keySpaceEnd1 = 63;

    uint64_t keySpaceStart2 = 63;
    uint64_t keySpaceEnd2 = 95;

    uint64_t keySpaceStart3 = 95;
    uint64_t keySpaceEnd3 = 127;

    thread t0 = thread(Encrypter<keySize>::bruteforce, plainText, cipherText, maxSeconds, keySpaceStart0, keySpaceEnd0);
    thread t1 = thread(Encrypter<keySize>::bruteforce, plainText, cipherText, maxSeconds, keySpaceStart1, keySpaceEnd1);
    thread t2 = thread(Encrypter<keySize>::bruteforce, plainText, cipherText, maxSeconds, keySpaceStart2, keySpaceEnd2);
    thread t3 = thread(Encrypter<keySize>::bruteforce, plainText, cipherText, maxSeconds, keySpaceStart3, keySpaceEnd3);

    // wait for all threads to finish
    t0.join();
    t1.join();
    t2.join();
    t3.join();

    // We could to 10^9 in ~2 minutes - so we estimate 30*10^9 iterations in an hour

    return 0;
}