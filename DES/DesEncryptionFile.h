#pragma once
#include <bitset>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <fstream>
#include <cmath>
#include "DesEncryption.h"
using namespace std;
using namespace boost::interprocess;
namespace des {
	const size_t	sizeOfBlock = 8;
	const size_t	bitsInByte = 8;
}

class DesEncryptionFile
{
	using Ull = unsigned long long;
public:
	DesEncryptionFile(Ull key) :key_(key) {
	}
	~DesEncryptionFile()
	{
		delete desEncryptor;
	}
	void encryptFile(const char* plainDatatFilename) {

		mapped_region plainDataRegion = mapFile(plainDatatFilename);
		plainDataAddr = static_cast<unsigned char*>(plainDataRegion.get_address());
		sizeOfData = plainDataRegion.get_size();

		createEmptyFile(encryptedDataFilename_, sizeOfData);

		mapped_region encryptedDataRegion = mapFile(encryptedDataFilename_);
		encryptedDataAddr = static_cast<Ull*>(encryptedDataRegion.get_address());
		numberOfBlocks = static_cast<size_t>(ceil(static_cast<double>(sizeOfData) / 8));//overload 

		encryptBlocks();
	}
	void setOutputFile(const char* filename) {
		encryptedDataFilename_ = filename;
	}
	void initializeDesEncryption(RoundKeyGenerator* roundKeyGenerator) {
		desEncryptor = new DesEncryption(key_, roundKeyGenerator);
	}

private:
	Ull				key_;
	const char*		plainTextFilename_;
	const char*		encryptedDataFilename_;
	unsigned char*	plainDataAddr;
	Ull*			encryptedDataAddr;
	size_t			sizeOfData;
	size_t			numberOfBlocks;
	DesEncryption*	desEncryptor;

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
	void encryptBlocks() {
		bitset<des::sizeOfBlock*des::bitsInByte>	plainDataBitsetUnit,
			encryptedDataBitsetUnit;

		for (size_t i = 0; i < numberOfBlocks; i++)
		{
			for (size_t j = 0; j < des::sizeOfBlock; j++)
			{
				plainDataBitsetUnit |= (static_cast<Ull>(plainDataAddr[i * des::bitsInByte + j]) << (j * des::bitsInByte));
			}
			encryptedDataBitsetUnit = desEncryptor->encrypt(plainDataBitsetUnit);
			encryptedDataAddr[i] = encryptedDataBitsetUnit.to_ullong();
			plainDataBitsetUnit = 0;
		}
	}
};