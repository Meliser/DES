#pragma once
#pragma once
#include <bitset>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <fstream>
#include <cmath>
#include "DesDecryption.h"
using namespace std;
using namespace boost::interprocess;
//const size_t	sizeOfBlock = 8;
//const size_t	bitsInByte = 8;
class DesDecryptionFile
{
	using Ull = unsigned long long;
public:
	DesDecryptionFile(Ull key) :key_(key) {
	}
	~DesDecryptionFile()
	{
		delete desDecryptor;
	}
	void decryptFile(const char* encryptedDatatFilename) {

		mapped_region encryptedDataRegion = mapFile(encryptedDatatFilename);
		encryptedDataAddr = static_cast<unsigned char*>(encryptedDataRegion.get_address());
		sizeOfData = encryptedDataRegion.get_size();

		createEmptyFile(decryptedDataFilename_, sizeOfData);

		mapped_region decryptedDataRegion = mapFile(decryptedDataFilename_);
		decryptedDataAddr = static_cast<Ull*>(decryptedDataRegion.get_address());
		numberOfBlocks = static_cast<size_t>(ceil(static_cast<double>(sizeOfData) / 8));//overload 

		decryptBlocks();
	}
	void setOutputFile(const char* filename) {
		decryptedDataFilename_ = filename;
	}
	void initializeDesDecryption(RoundKeyGenerator* roundKeyGenerator) {
		desDecryptor = new DesDecryption(key_, roundKeyGenerator);
	}

private:
	Ull				key_;
	const char*		encryptedDataFilename_;
	const char*		decryptedDataFilename_;
	unsigned char*	encryptedDataAddr;
	Ull*			decryptedDataAddr;
	size_t			sizeOfData;
	size_t			numberOfBlocks;
	DesDecryption*	desDecryptor;

	void createEmptyFile(const char* filename, size_t size) {
		std::ofstream file;
		file.open(filename, ios_base::binary);
		file.seekp(size - 1, 0);
		file << '\0';
		file.close();
	}
	mapped_region mapFile(const char* filename) {
		file_mapping mappedFile(filename, read_write);
		return mapped_region(mappedFile, read_write);
	}
	void decryptBlocks() {
		bitset<des::sizeOfBlock*des::bitsInByte>	encryptedDataBitsetUnit,
			decryptedDataBitsetUnit;

		for (size_t i = 0; i < numberOfBlocks; i++)
		{
			for (size_t j = 0; j < des::sizeOfBlock; j++)
			{
				encryptedDataBitsetUnit |= (static_cast<Ull>(encryptedDataAddr[i * des::bitsInByte + j]) << (j * des::bitsInByte));
			}
			decryptedDataBitsetUnit = desDecryptor->decrypt(encryptedDataBitsetUnit);
			decryptedDataAddr[i] = decryptedDataBitsetUnit.to_ullong();
			encryptedDataBitsetUnit = 0;
		}
	}
};