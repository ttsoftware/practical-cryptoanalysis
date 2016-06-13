#include "Encrypter.h"

template<size_t T>
bitset<T> Encrypter<T>::encrypt(bitset<T> key, bitset<T> plaintext) {
    bitset<2 * T> concatted = Encrypter<2 * T>::concat(key, plaintext);
    return Encrypter<2 * T>::md5Redux(concatted);
}

template<size_t T>
bitset<T> Encrypter<T>::hax(bitset<T> cipher, bitset<T> challenge, unordered_map<bitset<T>, bitset<T>> *map) {
    int chainLength = pow(2, 10);
    bitset<T> key = cipher;

    auto it = (*map).find(key);

    if(it != (*map).end()){
        cout << "Looking for key: " << key << " start("<< 0 << "): " << it->second << endl;
        return Encrypter<T>::chain(it->second, challenge, 1, chainLength, true);
    }

    bitset<T> prev;

    for (int i = chainLength; i >= 1; i--) {
        prev = key;
        key = Encrypter<T>::chain(cipher, challenge, i, chainLength, false);

        it = (*map).find(key);

        if (it != (*map).end()) {
            //Found a match on the cipher
            cout << "Looking for key: " << key << " start("<< i << "): " << it->second << endl;

            //chain used to find key lookup
            Encrypter<T>::chain(cipher, challenge, i, chainLength, true);

            cout << endl;

            //Full chain for match
            Encrypter<T>::chain(it->second, challenge, 1, chainLength, true);

            return Encrypter<T>::chain(it->second, challenge, 1, i, false);
        }
    }

    return NULL;
}


template<size_t T>
bitset<T> Encrypter<T>::chain(bitset<T> cipher,
                              bitset<T> challenge,
                              int rainbowFunction,
                              int chainLength,
                              bool print) {

    bitset<T> temp = cipher;

    for (; rainbowFunction <= chainLength; rainbowFunction++) {
        temp = Encrypter<T>::encrypt(temp, challenge);
        bitset<T> bitI(rainbowFunction);
        temp ^= bitI;

        if(print){
            cout << rainbowFunction << ": " << temp << endl;
        }

    }

    return temp;
}

template<size_t T>
bitset<28> Encrypter<T>::md5Redux(bitset<T> input) {

    char inputChars[T];
    for (int i = 0; i < T; i++) {
        inputChars[T-i-1] = input[i];
    }

    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char *) &inputChars, T, (unsigned char *) &digest);

    bitset<8 * MD5_DIGEST_LENGTH> md5Bits;

    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
        bitset<128> temp(digest[i]);

        temp <<= (MD5_DIGEST_LENGTH - i - 1)*8;

        md5Bits ^= temp;
//        bitset<8> test(digest[i]);
//        cout << "XOR char'" << test << "' at position "<< i << ":" << endl;
//        cout << temp << endl;
//        cout << md5Bits << endl;
    }

    return Encrypter<8 * MD5_DIGEST_LENGTH>::reduceSize(md5Bits);
}

template<size_t T>
void Encrypter<T>::breakKey(unordered_map<bitset<T>, bitset<T>> *map,
                            bitset<T> challenge,
                            bitset<T> secret) {

    bitset<T> cipher = Encrypter<T>::encrypt(secret, challenge);
    bitset<T> result = Encrypter<T>::hax(cipher, challenge, map);

    cout << "Result:" << endl;
    cout << result << endl;
    cout << "Actual:" << endl;
    cout << secret << endl;
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
        returnBits[i] = inputB[i];
    }
    for (int i = 28; i < 56; ++i) {
        returnBits[i] = inputA[i - 28];
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
            if (it == map.end()) {
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