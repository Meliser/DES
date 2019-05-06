#pragma once
#include "DesEncryption.h"

namespace des {
	class DesEncryptionBlocks
	{
	public:
		DesEncryptionBlocks(Ull key) :desEncryptor_(new DesEncryption(key)) {
		}
		~DesEncryptionBlocks() {
			delete desEncryptor_;
		}
		void encryptBlocks(unsigned char* plainDataAddr, size_t size, Ull* encryptedDataAddr)
		{
			bitset<blockSize>	plainDataBitsetUnit,
				encryptedDataBitsetUnit;

			size_t numberOfBlocks = static_cast<size_t>(ceil(static_cast<double>(size) / 8));//overload 
			for (size_t i = 0; i < numberOfBlocks; i++)
			{
				for (size_t j = 0; j < blockSize/bitsInByte; j++)
				{
					plainDataBitsetUnit |= (static_cast<Ull>(plainDataAddr[i * bitsInByte + j]) << (j * bitsInByte));
				}
				encryptedDataBitsetUnit = desEncryptor_->encrypt(plainDataBitsetUnit);
				encryptedDataAddr[i] = encryptedDataBitsetUnit.to_ullong();
				plainDataBitsetUnit = 0;
			}
		}

	private:
		DesEncryption *desEncryptor_;
	};
}






