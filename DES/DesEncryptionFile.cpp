#include "DesEncryptionFile.h"

void des::DesEncryptionFile::encryptFile(const char* plainDataFilename, const char* encryptedDataFilename) {
	try {
		plainDataRegion_ = mapFile(plainDataFilename);
	}
	catch (const std::exception&) {
		throw badFilenameException(plainDataFilename);
	}
	plainDataAddr_ = static_cast<const unsigned char*>(plainDataRegion_.get_address());
	sizeOfData_ = plainDataRegion_.get_size();
	
	createEmptyFile(encryptedDataFilename, sizeOfData_);

	try {
		encryptedDataRegion_ = mapFile(encryptedDataFilename);
	}
	catch (const std::exception&) {
		throw badFilenameException(encryptedDataFilename);
	}
	encryptedDataAddr_ = static_cast<Ull*>(encryptedDataRegion_.get_address());
	size_t numberOfBlocks = static_cast<size_t>(ceil(static_cast<double>(sizeOfData_) / 8));//overload 
	desEncryptorBlocks_.encryptBlocks(plainDataAddr_, sizeOfData_, encryptedDataAddr_, numberOfBlocks);
}



void des::DesEncryptionFile::createEmptyFile(const char* filename, size_t size) {
	std::ofstream file;
	file.open(filename, ios_base::binary);
	file.seekp(size - 1, 0);
	file << '\0';
	file.close();
}

mapped_region des::DesEncryptionFile::mapFile(const char* filename) {
	file_mapping mappedFile(filename, read_write);
	return mapped_region(mappedFile, read_write);
}


