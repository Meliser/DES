#pragma once
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <fstream>
#include <cmath>
#include "DesEncryption.h"
using namespace std;
using namespace boost::interprocess;
namespace enc {
	const size_t	sizeOfBlock = 8;
	const size_t	bitsInByte = 8;
}

class DesEncryptionFile
{
	using Ull = unsigned long long;
public:
	DesEncryptionFile(Ull key) :key_(key)
	{
	}
	~DesEncryptionFile()
	{
		delete desEncryptor;
	}
	void encryptFile(const char* plainDatatFilename);
	void setOutputFile(const char* filename);
	void initializeDesEncryption(RoundKeyGenerator* roundKeyGenerator);
private:
	Ull				key_;
	const char*		plainTextFilename_;
	const char*		encryptedDataFilename_;
	unsigned char*	plainDataAddr;
	Ull*			encryptedDataAddr;
	size_t			sizeOfData;
	size_t			numberOfBlocks;
	DesEncryption*	desEncryptor;

	void createEmptyFile(const char* filename, size_t size);
	mapped_region mapFile(const char* filename);
	void encryptBlocks();
};