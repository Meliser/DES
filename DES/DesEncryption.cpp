#include "DesEncryption.h"

DesEncryption::DesEncryption(unsigned long long key, RoundKeyGenerator *roundKeyGenerator_) : key_(key), roundKeyGenerator_(roundKeyGenerator_) {
	roundKeyGenerator_->initializeC0D0(key_);
	roundKeyGenerator_->generateRoundKeys(16);
}

bitset<64> DesEncryption::encrypt(const bitset<64> &plainText) {
	bitset<64>plainText_ = rearrange<64, 64>(plainText, IP);
	divideBitSets(lPart, rPart, plainText_);
	bitset<32> temp;
	for (size_t i = 0; i < 16; i++)
	{
		temp = lPart;
		lPart = rPart;
		rPart = (temp^feistelFunction(rPart, roundKeyGenerator_->getRoundKey(i)));

	}
	bitset<64> encrypted = combineBitSets(rPart, lPart);

	encrypted = rearrange<64, 64>(encrypted, FP);
	return encrypted;
}
