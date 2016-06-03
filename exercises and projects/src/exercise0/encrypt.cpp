#include "encrypt.h"

bitset<128> encrypt(bitset<128> key, bitset<128> plaintext) {
    return key ^ plaintext;
}