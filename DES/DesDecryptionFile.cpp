#include "DesDecryptionFile.h"

void des::DesDecryptionFile::decryptFile(const char* encryptedDatatFilename) {

	mapped_region encryptedDataRegion = mapFile(encryptedDatatFilename);
	encryptedDataAddr_ = static_cast<unsigned char*>(encryptedDataRegion.get_address());
	sizeOfData_ = encryptedDataRegion.get_size();

	createEmptyFile(decryptedDataFilename_, sizeOfData_);

	mapped_region decryptedDataRegion = mapFile(decryptedDataFilename_);
	decryptedDataAddr_ = static_cast<Ull*>(decryptedDataRegion.get_address());
	
	desDecryptorBlocks_.decryptBlocks(encryptedDataAddr_, sizeOfData_, decryptedDataAddr_);
	
}

void des::DesDecryptionFile::setOutputFile(const char* filename) {
	decryptedDataFilename_ = filename;
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


