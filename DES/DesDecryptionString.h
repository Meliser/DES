#pragma once
#include <string>
#include "DesDecryptionBlocks.h"

using std::string;

namespace des {
	class DesDecryptionString
	{
	public:
		DesDecryptionString(Ull key) :desDecryptorBlocks_(key), decryptedString_(nullptr) {
		}
		~DesDecryptionString();
		void decryptString(string encryptedString);
		Ull* getDecryptedString() {
			return decryptedString_;
		}
	private:
		DesDecryptionBlocks desDecryptorBlocks_;
		Ull* decryptedString_;
	};
}

