#include "DesEncryptionFile.h"

void des::DesEncryptionFile::encryptFile(const char* plainDataFilename) {
	
	mapped_region plainDataRegion = mapFile(plainDataFilename);
	plainDataAddr_ = static_cast<unsigned char*>(plainDataRegion.get_address());
	sizeOfData_ = plainDataRegion.get_size();
	
	createEmptyFile(encryptedDataFilename_, sizeOfData_);

	mapped_region encryptedDataRegion = mapFile(encryptedDataFilename_);
	encryptedDataAddr_ = static_cast<Ull*>(encryptedDataRegion.get_address());
	
	desEncryptorBlocks_.encryptBlocks(plainDataAddr_, sizeOfData_, encryptedDataAddr_);
	
}

void des::DesEncryptionFile::setOutputFile(const char* filename) {
	encryptedDataFilename_ = filename;
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

