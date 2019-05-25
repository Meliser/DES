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
		const string& getAccumulator()const {
			return accumulator;
		}
	private:
		DesEncryptionBlocks desEncryptorBlocks_;
		Ull* encryptedString_;
		string accumulator;
	};
}

