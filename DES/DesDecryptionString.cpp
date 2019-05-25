#include "DesDecryptionString.h"

des::DesDecryptionString::~DesDecryptionString() {
	delete decryptedString_;
}
void des::DesDecryptionString::decryptString(string encryptedString) {
	char* temp = new  char[encryptedString.size() + 1];

	strcpy_s(temp, encryptedString.size() + 1, encryptedString.c_str());

	size_t numberOfBlocks = encryptedString.size()/8;
	decryptedString_ = new Ull[numberOfBlocks];
	desDecryptorBlocks_.decryptBlocks(reinterpret_cast<const unsigned char*>(temp), encryptedString.size(), decryptedString_, numberOfBlocks);
	
	accumulator += reinterpret_cast<char*>(decryptedString_);
	accumulator.resize(numberOfBlocks * 8);
}
