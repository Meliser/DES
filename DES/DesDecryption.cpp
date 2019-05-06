#include "DesDecryption.h"

des::DesDecryption::DesDecryption(Ull key) : key_(key), roundKeyGenerator_(new RoundKeyGenerator){
	roundKeyGenerator_->initializeC0D0(key_);
	roundKeyGenerator_->generateRoundKeys(rounds);
}

des::DesDecryption::~DesDecryption()
{
	delete roundKeyGenerator_;
}

bitset<des::blockSize> des::DesDecryption::decrypt(bitset<blockSize> &cipherText) {
	bitset<blockSize>cipherText_ = rearrange<blockSize,IPSize>(cipherText, IP);

	divideBitSets(rPart_, lPart_, cipherText_);
	bitset<blockSize/2> temp;
	for (int i = rounds-1; i >= 0; i--)
	{
		temp = rPart_;
		rPart_ = lPart_;
		lPart_ = (temp^feistelFunction(rPart_, roundKeyGenerator_->getRoundKey(i)));
	}

	bitset<blockSize> decrypted = combineBitSets(lPart_, rPart_);

	decrypted = rearrange<blockSize, FPSize>(decrypted, FP);

	return decrypted;
}
