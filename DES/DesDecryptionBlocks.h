#pragma once
#include "DesDecryption.h"

namespace des {
	class DesDecryptionBlocks
	{
	public:
		DesDecryptionBlocks(Ull key) :desDecryptor_(new DesDecryption(key))
		{}
		~DesDecryptionBlocks();
		void decryptBlocks(	const unsigned char*	encryptedDataAddr,
							size_t					size,
							Ull*					decryptedDataAddr,
							size_t					numberOfBlocks);
	private:
		DesDecryption *desDecryptor_;
	};
}



