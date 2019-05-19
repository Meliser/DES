#include "DesEncryptionString.h"

des::DesEncryptionString::~DesEncryptionString() {
	delete encryptedString_;
}
void des::DesEncryptionString::encryptString(string plainString) {
	const unsigned char* temp = reinterpret_cast<const unsigned char*>(plainString.c_str());
	size_t numberOfBlocks = static_cast<size_t>(ceil(static_cast<double>(plainString.size()) / 8));
	encryptedString_ = new Ull[numberOfBlocks];
	desEncryptorBlocks_.encryptBlocks(temp, plainString.size(), encryptedString_, numberOfBlocks);
}