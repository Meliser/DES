#pragma once
#include <string>
#include "DesEncryptionBlocks.h"

using std::string;

namespace des {
	class DesEncryptionString
	{
	public:
		DesEncryptionString(Ull key) :desEncryptorBlocks_(key), encryptedString_(nullptr) {
		}
		~DesEncryptionString();
		void encryptString(string plainString);
		Ull* getEncryptedString() {
			return encryptedString_;
		}
	private:
		DesEncryptionBlocks desEncryptorBlocks_;
		Ull* encryptedString_;
	};
}

