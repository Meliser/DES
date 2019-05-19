#include "DesEncryptionBlocks.h"

des::DesEncryptionBlocks::~DesEncryptionBlocks() {
	delete desEncryptor_;
}
void des::DesEncryptionBlocks::encryptBlocks(	const unsigned char*	plainDataAddr,
												size_t					size,
												Ull*					encryptedDataAddr,
												size_t					numberOfBlocks)
{
	bitset<blockSize>	plainDataBitsetUnit,
		encryptedDataBitsetUnit;

	for (size_t i = 0; i < numberOfBlocks; i++)
	{
		for (size_t j = 0; j < blockSize / bitsInByte; j++)
		{
			plainDataBitsetUnit |= (static_cast<Ull>(plainDataAddr[i * bitsInByte + j]) << (j * bitsInByte));
		}
		encryptedDataBitsetUnit = desEncryptor_->encrypt(plainDataBitsetUnit);
		encryptedDataAddr[i] = encryptedDataBitsetUnit.to_ullong();
		plainDataBitsetUnit = 0;
	}
}