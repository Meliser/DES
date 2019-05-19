#pragma once
#include "DesEncryption.h"

namespace des {
	class DesEncryptionBlocks
	{
	public:
		DesEncryptionBlocks(Ull key) :desEncryptor_(new DesEncryption(key)) {
		}
		~DesEncryptionBlocks();
		void encryptBlocks(	const unsigned char*	plainDataAddr,
							size_t					size,
							Ull*					encryptedDataAddr,
							size_t					numberOfBlocks);

	private:
		DesEncryption *desEncryptor_;
	};
}






