#pragma once
#include "DesDecryption.h"

namespace des {
	class DesDecryptionBlocks
	{
	public:
		DesDecryptionBlocks(Ull key) :desDecryptor_(new DesDecryption(key))
		{}
		~DesDecryptionBlocks()
		{
			delete desDecryptor_;
		}

		void decryptBlocks(unsigned char * encryptedDataAddr, size_t size, Ull* decryptedDataAddr)
		{
			bitset<blockSize>	decryptedDataBitsetUnit,
								encryptedDataBitsetUnit;
			size_t numberOfBlocks = static_cast<size_t>(ceil(static_cast<double>(size) / 8));//overload 
			for (size_t i = 0; i < numberOfBlocks; i++)
			{
				for (size_t j = 0; j < blockSize/bitsInByte; j++)
				{
					encryptedDataBitsetUnit |= (static_cast<Ull>(encryptedDataAddr[i * bitsInByte + j]) << (j * bitsInByte));
				}
				decryptedDataBitsetUnit = desDecryptor_->decrypt(encryptedDataBitsetUnit);
				decryptedDataAddr[i] = decryptedDataBitsetUnit.to_ullong();
				encryptedDataBitsetUnit = 0;
			}
		}

	private:
		DesDecryption *desDecryptor_;
	};
}



