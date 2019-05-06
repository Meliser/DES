#include "DesEncryption.h"

des::DesEncryption::DesEncryption(Ull key) : key_(key){
	roundKeyGenerator_ = new RoundKeyGenerator;
	roundKeyGenerator_->initializeC0D0(key_);
	roundKeyGenerator_->generateRoundKeys(rounds);
}
des::DesEncryption::~DesEncryption()
{
	delete roundKeyGenerator_;
}

bitset<des::blockSize> des::DesEncryption::encrypt(const bitset<blockSize> &plainText) {
	bitset<blockSize>plainText_ = rearrange<blockSize,IPSize>(plainText, IP);
	divideBitSets(lPart_, rPart_, plainText_);
	bitset<blockSize/2> temp;
	for (size_t i = 0; i < rounds; i++)
	{
		temp = lPart_;
		lPart_ = rPart_;
		rPart_ = (temp^feistelFunction(rPart_, roundKeyGenerator_->getRoundKey(i)));

	}
	bitset<blockSize> encrypted = combineBitSets(rPart_, lPart_);

	encrypted = rearrange<blockSize, FPSize>(encrypted, FP);
	return encrypted;
}
