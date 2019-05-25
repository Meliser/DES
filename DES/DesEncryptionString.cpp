#include "DesEncryptionString.h"

des::DesEncryptionString::~DesEncryptionString() {
	delete encryptedString_;
}
void des::DesEncryptionString::encryptString(string plainString) {
	
	 char* temp = new  char[plainString.size() + 1];
	 
	 strcpy_s(temp, plainString.size()+1, plainString.c_str());

	size_t numberOfBlocks = static_cast<size_t>(ceil(static_cast<double>(plainString.size()) / 8));
	encryptedString_ = new Ull[numberOfBlocks];
	desEncryptorBlocks_.encryptBlocks(reinterpret_cast<const unsigned char*>(temp), plainString.size(), encryptedString_, numberOfBlocks);
	
		accumulator += reinterpret_cast<char*>(encryptedString_);
	
	accumulator.resize(numberOfBlocks*8);
	
}