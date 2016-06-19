#include "Encrypter.h"

template<size_t T>
void Encrypter<T>::testKeysForward(unsigned char *plaintext, unordered_map<bitset<64>, vector< bitset<20> > > *map){

    //Init starting variables
    int maxKey = pow(2,20);
    bitset<20> key(0);
    bitset<64> result(0);
    unsigned char output[8];

    for(int i = 0; i < maxKey; i++){
        //Encrypt the plaintext with the given key and write it to output
        Encrypter<8>::encrypt(plaintext, (unsigned char *) output, key, true);

        //Convert the resulting bytes to a bitset
        result = Encrypter<8>::toBitset((unsigned char *) output);

        //Look up in the map
        auto it = (*map).find(result);

        //If none found, add a new vector to the map
        if(it == (*map).end() ){
            vector<bitset<20>> temp;
            (*map)[result] = temp;
        }

        //Add the key to the vector for the given result
        (*map)[result].push_back(key);

        //Increment key
        key = Encrypter<20>::increment(key);
    }
}

template<size_t T>
void Encrypter<T>::testKeysBackward(unsigned char *cipher, unordered_map<bitset<64>, vector<bitset<20>>> *map, vector<tuple<bitset<20>,bitset<20>>> *pairs){

    //Init starting variables
    int maxKey = pow(2,20);
    bitset<20> key(0);
    bitset<64> result(0);
    unsigned char output[8];

    for(int i = 0; i < maxKey; i++){

        //Decrypt backwards using the given key and the cipher
        Encrypter<8>::encrypt(cipher, (unsigned char *) output, key, false);

        //Convert the result to bitset
        result = Encrypter<8>::toBitset((unsigned char *) output);

        //Lookup in the map
        auto it = (*map).find(result);

        if(it != (*map).end() ){
            //Scan through vector. All matches are candidate keys.
            for(int j = 0; j< it->second.size(); j++){
                (*pairs).push_back(make_pair(it->second[j], key));
                cout << "MATCH: " << it->second[j] << " : " << key << endl;
            }
        }
        //Increment the key
        key = Encrypter<20>::increment(key);
    }
}


template<size_t T>
void Encrypter<T>::encrypt(unsigned char* input, unsigned char* output, bitset<20> key, bool encrypt){

    //Set encryption flag
    int enc = encrypt
              ? DES_ENCRYPT
              : DES_DECRYPT;

    //Assign key somehow
    unsigned char convertedKey[7];
    DES_key_schedule keySchedule;

    //Converted key will be written to the pointer given
    Encrypter<8>::convertKey(key, convertedKey);

    //do shit
    DES_set_key_unchecked((C_Block *) &convertedKey, &keySchedule);

    //What is dis
    DES_ecb_encrypt((C_Block *) input, (C_Block *) output, &keySchedule, enc);
}

template<size_t T>
bitset<T * 8> Encrypter<T>::toBitset(unsigned char * input){
    bitset<T * 8> result;

    //Apply every char to the result bitset
    for (int i = 0; i < T; ++i) {

        //Create new bitset containing the char as bits
        bitset<T * 8> temp(input[i]);

        //Bitshift the char corresponding to the position in the digest
        temp <<= (T - i - 1) * 8;

        //Xor the char onto result
        result ^= temp;
    }

    return result;
}

template<size_t T>
void Encrypter<T>::convertKey(bitset<20> key, unsigned char * output){

    //The overall index of the key processed
    int keyIndex = 0;

    //Loop through each character of the output
    for(int ch = 0; ch < T; ch++) {

        //bitset for each character
        bitset<8> charbitset(0);

        //Loop through each bit corresponding to the character in the output
        for (int i = 1; i < T; i++) {

            //Terminate when length of key is found
            if (keyIndex > 19) break;

            //Set the bit found
            charbitset[i] = key[keyIndex];
            keyIndex++;
        }

        //Convert to char. Insert in char array from the back
        unsigned long i = charbitset.to_ulong();
        output[7 - ch - 1] = static_cast<unsigned char>( i );
    }
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