#pragma once
#include "RoundKeyGenerator.h"
#include <iostream>
#include "feistelFunction.h"

using namespace std;

class DesDecryption {
public:
	DesDecryption(unsigned long long key, RoundKeyGenerator* roundKeyGenerator) : key_(key), roundKeyGenerator_(roundKeyGenerator) {
		roundKeyGenerator_->initializeC0D0(key_);
		roundKeyGenerator_->generateRoundKeys(16);
	}
	bitset<64> decrypt(bitset<64> &cipherText) {
		bitset<64>cipherText_ = rearrange<64, 64>(cipherText, IP);
		//cout << "cipherText: ";
		//cout << hex << cipherText_.to_ullong() << endl;

		divideBitSets(rPart, lPart, cipherText_);
		bitset<32> temp;
		for (int i = 15; i >= 0; i--)
		{
			temp = rPart;
			rPart = lPart;
			lPart = (temp^feistelFunction(rPart, roundKeyGenerator_->getRoundKey(i)));
		}

		bitset<64> decrypted = combineBitSets(lPart, rPart);

		decrypted = rearrange<64, 64>(decrypted, FP);
		//cout << "decrypted: ";
		//cout << hex << decrypted.to_ullong() << endl;
		return decrypted;
	}
private:
	bitset<keySize> key_;
	RoundKeyGenerator *roundKeyGenerator_;
	bitset<32> lPart;
	bitset<32> rPart;
};