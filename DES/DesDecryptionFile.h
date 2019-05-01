#pragma once
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <fstream>
#include <cmath>
#include "DesDecryption.h"
using namespace std;
using namespace boost::interprocess;
namespace dec {
	const size_t	sizeOfBlock = 8;
	const size_t	bitsInByte = 8;
}

class DesDecryptionFile
{
	using Ull = unsigned long long;
public:
	DesDecryptionFile(Ull key) :key_(key)
	{
	}
	~DesDecryptionFile()
	{
		delete desDecryptor;
	}
	void decryptFile(const char* encryptedDatatFilename);
	void setOutputFile(const char* filename);
	void initializeDesDecryption(RoundKeyGenerator* roundKeyGenerator);

private:
	Ull				key_;
	const char*		encryptedDataFilename_;
	const char*		decryptedDataFilename_;
	unsigned char*	encryptedDataAddr;
	Ull*			decryptedDataAddr;
	size_t			sizeOfData;
	size_t			numberOfBlocks;
	DesDecryption*	desDecryptor;

	void createEmptyFile(const char* filename, size_t size);
	mapped_region mapFile(const char* filename);
	void decryptBlocks();
};