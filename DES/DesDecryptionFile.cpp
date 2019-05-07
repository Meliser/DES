#include "DesDecryptionFile.h"

void des::DesDecryptionFile::decryptFile(const char* encryptedDataFilename, const char* decryptedDataFilename) {
	try {
		encryptedDataRegion_ = mapFile(encryptedDataFilename);
	}
	catch (std::exception&) {
		throw badFilenameException(encryptedDataFilename);
	}
	encryptedDataAddr_ = static_cast<unsigned char*>(encryptedDataRegion_.get_address());
	sizeOfData_ = encryptedDataRegion_.get_size();
	
	createEmptyFile(decryptedDataFilename, sizeOfData_);

	try {
		decryptedDataRegion_ = mapFile(decryptedDataFilename);
	}
	catch (std::exception&) {
		throw badFilenameException(encryptedDataFilename);
	}
	decryptedDataAddr_ = static_cast<Ull*>(decryptedDataRegion_.get_address());
	desDecryptorBlocks_.decryptBlocks(encryptedDataAddr_, sizeOfData_, decryptedDataAddr_);
}

void des::DesDecryptionFile::createEmptyFile(const char* filename, size_t size) {
	std::ofstream file;
	file.open(filename, ios_base::binary);
	file.seekp(size - 1, 0);
	file << '\0';
	file.close();
}

mapped_region des::DesDecryptionFile::mapFile(const char* filename) {
	file_mapping mappedFile(filename, read_write);
	return mapped_region(mappedFile, read_write);
}


