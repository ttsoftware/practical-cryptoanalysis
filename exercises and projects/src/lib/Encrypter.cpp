#include "Encrypter.h"

template<size_t T>
vector<bitset<T>> Encrypter<T>::hax(bitset<T> cipher, bitset<T> challenge, unordered_map<bitset<T>, bitset<T>> *map) {

    int chainLength = pow(2, 10);
    bitset<T> key = cipher;

    //Assign a result set
    vector<bitset<T>> list;

    //Check if the key is in the table.
    auto it = (*map).find(key);
    if(it != (*map).end()){
        list.push_back(Encrypter<T>::chain(it->second, challenge, 1, chainLength-1) ^ bitset<28>(chainLength));
    }

    for (int i = chainLength; i >= 1; i--) {
        //Apply rainbow function to cipher
        key = Encrypter<T>::chain(cipher, challenge, i, chainLength);

        //Lookup key
        it = (*map).find(key);

        if (it != (*map).end()) {
            //Found a match on the cipher
            //Find the key from the chain that matched and apply XOR to find the actual input given to the MD5 function.
            list.push_back(Encrypter<T>::chain(it->second, challenge, 1, i-2) ^ bitset<28>(i-1));
        }
    }

    return list;
}

template<size_t T>
bitset<T> Encrypter<T>::chain(bitset<T> cipher,
                              bitset<T> challenge,
                              int rainbowFunction,
                              int chainLength) {

    bitset<T> temp = cipher;

    //Runs through all rainbow functions until limit is reached
    for (; rainbowFunction <= chainLength; rainbowFunction++) {

        //XOR first, then encrypt
        bitset<T> bitI(rainbowFunction);
        temp ^= bitI;
        temp = Encrypter<T>::encrypt(temp, challenge);
    }

    return temp;
}

template<size_t T>
bitset<28> Encrypter<T>::md5Redux(bitset<T> input) {

    //Convert all bits to a char array in opposite order.
    char inputChars[T];
    for (int i = 0; i < T; i++) {
        inputChars[T-i-1] = input[i];
    }

    //Assign result array and run MD5 function
    unsigned char digest[MD5_DIGEST_LENGTH];
    MD5((unsigned char *) &inputChars, T, (unsigned char *) &digest);

    //Assign bitset for result
    bitset<8 * MD5_DIGEST_LENGTH> md5Bits;

    //Apply every char to the result bitset
    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {

        //Create new bitset containing the char as bits
        bitset<128> temp(digest[i]);

        //Bitshift the char corresponding to the possition in the digest
        temp <<= (MD5_DIGEST_LENGTH - i - 1)*8;

        //XOR onto our result
        md5Bits ^= temp;
    }

    //Return the reduced bitset
    return Encrypter<8 * MD5_DIGEST_LENGTH>::reduceSize(md5Bits);
}

template<size_t T>
bool Encrypter<T>::breakKey(unordered_map<bitset<T>, bitset<T>> *map,
                            bitset<T> challenge,
                            bitset<T> secret) {

    //Find cipher and test all possibilities
    bitset<T> cipher = Encrypter<T>::encrypt(secret, challenge);
    vector<bitset<T>> result = Encrypter<T>::hax(cipher, challenge, map);

    bool match = false;

    for(int i = 0; i < result.size(); i++){
        //Could also find this by encrypting the challenge with the candidate key and check
        //that the corresponding cipher was the same.
        if(result[i] == secret){
            match = true;
            break;
        }
    }

    return match;
}

template<size_t T>
bitset<T> Encrypter<T>::encrypt(bitset<T> key, bitset<T> plaintext) {
    //Concat the two, then apply md5 function. Return reduced output.
    bitset<2 * T> concat = Encrypter<2 * T>::concat(key, plaintext);
    return Encrypter<2 * T>::md5Redux(concat);
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
    //Copies the lowest 28 bits to the new bitset and return
    for (size_t i = 0; i < 28; ++i) {
        returnBits[i] = input[i];
    }
    return returnBits;
}

template<size_t T>
bitset<56> Encrypter<T>::concat(bitset<28> inputA, bitset<28> inputB) {
    bitset<56> returnBits(0);
    //Concats bits from input B first, then A
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

            //Check if the key does not already exist. Should not be any collisions.
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

    //Write every pair to file seperated by ":"
    for (auto it = map->begin(); it != map->end(); ++it) {
        dump << it->first << ":" << it->second << std::endl;
    }

    dump.close();
}