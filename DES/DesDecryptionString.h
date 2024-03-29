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
		const string& getAccumulator()const {
			return accumulator;
		}
	private:
		DesDecryptionBlocks desDecryptorBlocks_;
		Ull* decryptedString_;
		string accumulator;
	};
}

