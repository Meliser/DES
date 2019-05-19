#include "DesDecryptionBlocks.h"

des::DesDecryptionBlocks::~DesDecryptionBlocks()
{
	delete desDecryptor_;
}

void des::DesDecryptionBlocks::decryptBlocks(	const unsigned char*	encryptedDataAddr,
												size_t					size,
												Ull*					decryptedDataAddr,
												size_t					numberOfBlocks)
{
	bitset<blockSize>	decryptedDataBitsetUnit,
						encryptedDataBitsetUnit;
	for (size_t i = 0; i < numberOfBlocks; i++)
	{
		for (size_t j = 0; j < blockSize / bitsInByte; j++)
		{
			encryptedDataBitsetUnit |= (static_cast<Ull>(encryptedDataAddr[i * bitsInByte + j]) << (j * bitsInByte));
		}
		decryptedDataBitsetUnit = desDecryptor_->decrypt(encryptedDataBitsetUnit);
		decryptedDataAddr[i] = decryptedDataBitsetUnit.to_ullong();
		encryptedDataBitsetUnit = 0;
	}
}