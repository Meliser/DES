#pragma once
#include "RoundKeyGenerator.h"
#include "feistelFunction.h"

using namespace std;

class DesDecryption {
public:
	DesDecryption(unsigned long long key, RoundKeyGenerator* roundKeyGenerator);
	bitset<64> decrypt(bitset<64> &cipherText);
private:
	bitset<keySize> key_;
	RoundKeyGenerator *roundKeyGenerator_;
	bitset<32> lPart;
	bitset<32> rPart;
};