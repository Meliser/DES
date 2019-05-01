#pragma once
#include "RoundKeyGenerator.h"
#include "feistelFunction.h"

class DesEncryption {
public:
	DesEncryption(unsigned long long key, RoundKeyGenerator *roundKeyGenerator_);
	bitset<64> encrypt(const bitset<64> &plainText);
private:
	bitset<keySize> key_;
	RoundKeyGenerator *roundKeyGenerator_;
	bitset<32> lPart;
	bitset<32> rPart;
};