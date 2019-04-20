#pragma once
#include "RoundKeyGenerator.h"
#include <iostream>
#include "feistelFunction.h"

class DesEncryption {
public:
	DesEncryption(unsigned long long key, RoundKeyGenerator *roundKeyGenerator_) : key_(key), roundKeyGenerator_(roundKeyGenerator_) {
		roundKeyGenerator_->initializeC0D0(key_);
		roundKeyGenerator_->generateRoundKeys(16);
	}
	void encrypt(const bitset<64> &plainText) {

		bitset<64>plainText_ = rearrange<64, 64>(plainText, IP);
		divideBitSets(lPart, rPart, plainText_);

		cout << "plainText: ";
		cout << hex << plainText_.to_ullong() << endl;
		bitset<32> temp;
		for (size_t i = 0; i < 16; i++)
		{
			temp = lPart;
			lPart = rPart;
			rPart = (temp^feistelFunction(rPart, roundKeyGenerator_->getRoundKey(i)));

		}
		bitset<64> encrypted = combineBitSets(rPart, lPart);

		encrypted = rearrange<64, 64>(encrypted, FP);
		cout << "encrypted: ";
		cout << hex << encrypted.to_ullong() << endl;

	}

private:
	bitset<keySize> key_;
	RoundKeyGenerator *roundKeyGenerator_;
	bitset<32> lPart;
	bitset<32> rPart;

};