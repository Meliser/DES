#include "DesDecryption.h"

DesDecryption::DesDecryption(unsigned long long key, RoundKeyGenerator* roundKeyGenerator) : key_(key), roundKeyGenerator_(roundKeyGenerator) {
	roundKeyGenerator_->initializeC0D0(key_);
	roundKeyGenerator_->generateRoundKeys(16);
}

bitset<64> DesDecryption::decrypt(bitset<64> &cipherText) {
	bitset<64>cipherText_ = rearrange<64, 64>(cipherText, IP);


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

	return decrypted;
}
