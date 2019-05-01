#include "DesEncryptionFile.h"

void DesEncryptionFile::encryptFile(const char* plainDatatFilename) {

	mapped_region plainDataRegion = mapFile(plainDatatFilename);
	plainDataAddr = static_cast<unsigned char*>(plainDataRegion.get_address());
	sizeOfData = plainDataRegion.get_size();

	createEmptyFile(encryptedDataFilename_, sizeOfData);

	mapped_region encryptedDataRegion = mapFile(encryptedDataFilename_);
	encryptedDataAddr = static_cast<Ull*>(encryptedDataRegion.get_address());
	numberOfBlocks = static_cast<size_t>(ceil(static_cast<double>(sizeOfData) / 8));//overload 

	encryptBlocks();
}

void DesEncryptionFile::setOutputFile(const char* filename) {
	encryptedDataFilename_ = filename;
}

void DesEncryptionFile::initializeDesEncryption(RoundKeyGenerator* roundKeyGenerator) {
	desEncryptor = new DesEncryption(key_, roundKeyGenerator);
}

void DesEncryptionFile::createEmptyFile(const char* filename, size_t size) {
	std::ofstream file;
	file.open(filename, ios_base::binary);
	file.seekp(size - 1, 0);
	file << '\0';
	file.close();
}

mapped_region DesEncryptionFile::mapFile(const char* filename) {
	file_mapping mappedFile(filename, read_write);
	return mapped_region(mappedFile, read_write);
}

void DesEncryptionFile::encryptBlocks() {
	bitset<enc::sizeOfBlock*enc::bitsInByte>	plainDataBitsetUnit,
		encryptedDataBitsetUnit;

	for (size_t i = 0; i < numberOfBlocks; i++)
	{
		for (size_t j = 0; j < enc::sizeOfBlock; j++)
		{
			plainDataBitsetUnit |= (static_cast<Ull>(plainDataAddr[i * enc::bitsInByte + j]) << (j * enc::bitsInByte));
		}
		encryptedDataBitsetUnit = desEncryptor->encrypt(plainDataBitsetUnit);
		encryptedDataAddr[i] = encryptedDataBitsetUnit.to_ullong();
		plainDataBitsetUnit = 0;
	}
}
