#include "DesDecryptionString.h"

des::DesDecryptionString::~DesDecryptionString() {
	delete decryptedString_;
}
void des::DesDecryptionString::decryptString(string encryptedString) {
	const unsigned char* temp = reinterpret_cast<const unsigned char*>(encryptedString.c_str());
	size_t numberOfBlocks = static_cast<size_t>(ceil(static_cast<double>(encryptedString.size()) / 8));
	decryptedString_ = new Ull[numberOfBlocks];
	desDecryptorBlocks_.decryptBlocks(temp, encryptedString.size(), decryptedString_, numberOfBlocks);
}
