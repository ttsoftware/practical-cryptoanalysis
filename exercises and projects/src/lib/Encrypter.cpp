#include "Encrypter.h"

template<size_t T>
bitset<T> Encrypter<T>::encrypt(bitset<T> key, bitset<T> plaintext) {
    bitset<2 * T> concatted = Encrypter<2 * T>::concat(key, plaintext);
    return Encrypter<2 * T>::md5Redux(concatted);
}

template<size_t T>
void Encrypter<T>::chain(bitset<T> input,
                         bitset<T> challenge,
                         unordered_map<bitset<T>, bitset<T>> *rainbowTable) {

    int chainLength = pow(2, 10);
    bitset<28> chainDigest(0);

    for (int i = 1; i < chainLength; i++) {
        bitset<28> chainDigest = Encrypter<28>::encrypt(input, challenge);
        bitset<T> bitI(i);
        chainDigest ^= bitI;
    }

    (*rainbowTable)[input] = chainDigest;
}

template<size_t T>
bitset<T> Encrypter<T>::hax(bitset<T> cipher, bitset<T> challenge, unordered_map<bitset<T>, bitset<T>> *map) {
    int chainLength = pow(2, 10);
    bitset<T> key = cipher;

    auto it = (*map).find(key);

    if(it != (*map).end()){
        cout << "Looking for key: " << key << " start: " << it->second;
        return Encrypter<T>::chainLookup(it->second, challenge, 0, chainLength);
    }

    for (int i = 1; i < chainLength; i++) {
        key = Encrypter<T>::rainbowLookup(key, challenge, i, chainLength);

        it = (*map).find(key);

        if (it != (*map).end()) {
            //Found a match on the cipher
            cout << "Looking for key: " << key << " start: " << it->second;
            return Encrypter<T>::chainLookup(it->second, challenge, i, chainLength);
        }
    }

    return NULL;
}


template<size_t T>
bitset<T> Encrypter<T>::rainbowLookup(bitset<T> cipher, bitset<T> challenge, int rainbowFunction, int chainLength) {

    bitset<T> temp = cipher;

    for (; rainbowFunction < chainLength; rainbowFunction++) {
        temp = Encrypter<T>::encrypt(temp, challenge);

        bitset<T> bitI(rainbowFunction);
        temp ^= bitI;
    }

    return temp;
}

template<size_t T>
bitset<28> Encrypter<T>::md5Redux(bitset<T> input) {

    char inputChars[T];
    for (int i = 0; i < T; i++) {
        inputChars[i] = input[i];
    }

    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char *) &inputChars, T, (unsigned char *) &digest);

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
void Encrypter<T>::breakKey(unordered_map<bitset<T>, bitset<T>> *map,
                            bitset<T> challenge, bitset<T> secret) {

    bitset<T> cipher = Encrypter<T>::encrypt(secret, challenge);
    bitset<T> result = Encrypter<T>::hax(cipher, challenge, map);

    cout << "Result:" << endl;
    cout << result << endl;
    cout << "Actual:" << endl;
    cout << secret << endl;
}

template<size_t T>
bitset<T> Encrypter<T>::chainLookup(bitset<T> start, bitset<T> challenge, int rainbowFunction, int chainLength) {

    bitset<T> key = start;

    for (int i = 1; i < (chainLength - rainbowFunction); i++) {
        cout << key << endl;
        key = Encrypter<T>::encrypt(key, challenge);
        bitset<T> bitI(i);
        key ^= bitI;
    }

    return key;
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
bitset<28> Encrypter<T>::reduceSize(bitset<T> input) {
    bitset<28> returnBits(0);
    for (size_t i = 0; i < 28; ++i) {
        returnBits[i] = input[i];
    }
    return returnBits;
}

template<size_t T>
bitset<56> Encrypter<T>::concat(bitset<28> inputA, bitset<28> inputB) {
    bitset<56> returnBits(0);
    for (int i = 0; i < 28; ++i) {
        returnBits[i] = inputA[i];
    }
    for (int i = 28; i < 56; ++i) {
        returnBits[i] = inputB[i - 28];
    }
    return returnBits;
}

template<size_t T>
unordered_map<bitset<T>, bitset<T>> Encrypter<T>::loadFromFile(string path) {
    string line;
    ifstream filestream(path);

    unordered_map<bitset<T>, bitset<T>> map;

    if (filestream.is_open()) {
        while (getline(filestream, line)) {


            int del_position = line.find(":");
            string first = line.substr(0, del_position);
            string last = line.substr(del_position + 1, line.length());

            bitset<T> key(first);
            bitset<T> value(last);

            auto it = map.find(key);
            if(it == map.end()){
                map.insert(make_pair(key, value));
            }
        }
    }

    filestream.close();

    return map;
}

template<size_t T>
void Encrypter<T>::writeToFile(unordered_map<bitset<T>, bitset<T>> *map, string path) {
    ofstream dump;
    dump.open(path);

    for (auto it = map->begin(); it != map->end(); ++it) {
        dump << it->first << ":" << it->second << std::endl;
    }

    dump.close();
}