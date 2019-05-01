#include "DesDecryptionFile.h"

void DesDecryptionFile::decryptFile(const char* encryptedDatatFilename) {

	mapped_region encryptedDataRegion = mapFile(encryptedDatatFilename);
	encryptedDataAddr = static_cast<unsigned char*>(encryptedDataRegion.get_address());
	sizeOfData = encryptedDataRegion.get_size();

	createEmptyFile(decryptedDataFilename_, sizeOfData);

	mapped_region decryptedDataRegion = mapFile(decryptedDataFilename_);
	decryptedDataAddr = static_cast<Ull*>(decryptedDataRegion.get_address());
	numberOfBlocks = static_cast<size_t>(ceil(static_cast<double>(sizeOfData) / 8));//overload 

	decryptBlocks();
}

void DesDecryptionFile::setOutputFile(const char* filename) {
	decryptedDataFilename_ = filename;
}

void DesDecryptionFile::initializeDesDecryption(RoundKeyGenerator* roundKeyGenerator) {
	desDecryptor = new DesDecryption(key_, roundKeyGenerator);
}

void DesDecryptionFile::createEmptyFile(const char* filename, size_t size) {
	std::ofstream file;
	file.open(filename, ios_base::binary);
	file.seekp(size - 1, 0);
	file << '\0';
	file.close();
}

mapped_region DesDecryptionFile::mapFile(const char* filename) {
	file_mapping mappedFile(filename, read_write);
	return mapped_region(mappedFile, read_write);
}

void DesDecryptionFile::decryptBlocks() {
	bitset<dec::sizeOfBlock*dec::bitsInByte>	encryptedDataBitsetUnit,
		decryptedDataBitsetUnit;

	for (size_t i = 0; i < numberOfBlocks; i++)
	{
		for (size_t j = 0; j < dec::sizeOfBlock; j++)
		{
			encryptedDataBitsetUnit |= (static_cast<Ull>(encryptedDataAddr[i * dec::bitsInByte + j]) << (j * dec::bitsInByte));
		}
		decryptedDataBitsetUnit = desDecryptor->decrypt(encryptedDataBitsetUnit);
		decryptedDataAddr[i] = decryptedDataBitsetUnit.to_ullong();
		encryptedDataBitsetUnit = 0;
	}
}
