#include "Encrypter.h"

template<size_t T>
void Encrypter<T>::testKeysForward(unsigned char *plaintext, unordered_map<bitset<64>, vector< bitset<20> > > *map){

    int maxKey = pow(2,20);
    bitset<20> key(0);
    bitset<64> result(0);
    unsigned char output[8];

    for(int i = 0; i < maxKey; i++){

        Encrypter<8>::encrypt(plaintext, (unsigned char *) output, key, true);
        result = Encrypter<8>::toBitset((unsigned char *) output);

        auto it = (*map).find(result);

        if(it == (*map).end() ){
            vector<bitset<20>> temp;
            (*map)[result] = temp;

        }
        (*map)[result].push_back(key);

        key = Encrypter<20>::increment(key);

//        cout << i << ": "<<(*map).size() << endl;
    }
}

template<size_t T>
void Encrypter<T>::testKeysBackward(unsigned char *cipher, unordered_map<bitset<64>, vector<bitset<20>>> *map, vector<tuple<bitset<20>,bitset<20>>> *pairs){
    int maxKey = pow(2,20);
    bitset<20> key(0);
    bitset<64> result(0);
    unsigned char output[8];

    for(int i = 0; i < maxKey; i++){

        Encrypter<8>::encrypt(cipher, (unsigned char *) output, key, false);
        result = Encrypter<8>::toBitset((unsigned char *) output);

        auto it = (*map).find(result);

        if(it != (*map).end() ){
            for(int j = 0; j< it->second.size(); j++){
                (*pairs).push_back(make_pair(it->second[j], key));
                cout << "MATCH BITCHES: "<< it->second[j] << " : " << key << endl;
            }

        }
        key = Encrypter<20>::increment(key);

//        cout << i << ": "<<(*pairs).size() << endl;
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

    //This was to check that the key is converted correctly - now it is
//    Encrypter<7>::toBitset((unsigned char *) &convertedKey);

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

        //Bitshift the char corresponding to the possition in the digest
        temp <<= (T - i - 1) * 8;

//        cout << "Iteration " << i << endl;
//        cout << temp << endl;

        //XOR onto our result
        result ^= temp;

//        cout << result << endl;
    }

    return result;
}

template<size_t T>
void Encrypter<T>::convertKey(bitset<20> key, unsigned char * output){

    int keyIndex = 0;
    for(int ch = 0; ch < T; ch++) {

        //bitset for each character
        bitset<8> charbitset(0);

        for (int i = 1; i < T; i++) {

            //KeyIndex should always have the lowest bit unset because of parity
//            int keyIndex = i - 1 + ch * T;

            //Terminate when length of key is found
            if (keyIndex > 19) break;

            charbitset[i] = key[keyIndex];
            keyIndex++;
        }

        //Convert to char. Insert in char array from the back
        unsigned long i = charbitset.to_ulong();
        output[7 - ch - 1] = static_cast<unsigned char>( i );
    }
}


//template<size_t T>
//bitset<28> Encrypter<T>::md5Redux(bitset<T> input) {
//
//    //Convert all bits to a char array in opposite order.
//    char inputChars[T];
//    for (int i = 0; i < T; i++) {
//        inputChars[T-i-1] = input[i];
//    }
//
//    //Assign result array and run MD5 function
//    unsigned char digest[MD5_DIGEST_LENGTH];
//    MD5((unsigned char *) &inputChars, T, (unsigned char *) &digest);
//
//    //Assign bitset for result
//    bitset<8 * MD5_DIGEST_LENGTH> md5Bits;
//
//    //Apply every char to the result bitset
//    for (int i = 0; i < MD5_DIGEST_LENGTH; ++i) {
//
//        //Create new bitset containing the char as bits
//        bitset<128> temp(digest[i]);
//
//        //Bitshift the char corresponding to the possition in the digest
//        temp <<= (MD5_DIGEST_LENGTH - i - 1)*8;
//
//        //XOR onto our result
//        md5Bits ^= temp;
//    }
//
//    //Return the reduced bitset
//    return Encrypter<8 * MD5_DIGEST_LENGTH>::reduceSize(md5Bits);
//}

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