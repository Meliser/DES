#include <iostream>
#include <bitset>
#include <array>
#include "Timer.h"
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <fstream>
#include <string>
#include <cmath>
#include "DesEncryptionFile.h"
#include "DesDecryptionFile.h"


using namespace std;
using namespace boost::interprocess;
//const size_t	sizeOfBlock = 8;
//const size_t	bitsInByte = 8;
//class DesEncryptionFile
//{
//	using Ull = unsigned long long;
//public:
//	DesEncryptionFile(Ull key):key_(key){
//	}
//	~DesEncryptionFile()
//	{
//		delete desEncryptor;
//	}
//	void encryptFile(const char* plainDatatFilename) {
//		
//		mapped_region plainDataRegion = mapFile(plainDatatFilename);
//		plainDataAddr = static_cast<unsigned char*>(plainDataRegion.get_address());
//		sizeOfData = plainDataRegion.get_size();
//
//		createEmptyFile(encryptedDataFilename_, sizeOfData);
//
//		mapped_region encryptedDataRegion = mapFile(encryptedDataFilename_);
//		encryptedDataAddr = static_cast<Ull*>(encryptedDataRegion.get_address());
//		numberOfBlocks = static_cast<size_t>(ceil(static_cast<double>(sizeOfData) / 8));//overload 
//
//		encryptBlocks();
//	}
//	void setOutputFile(const char* filename) {
//		encryptedDataFilename_ = filename;
//	}
//	void initializeDesEncryption(RoundKeyGenerator* roundKeyGenerator) {
//		desEncryptor = new DesEncryption(key_, roundKeyGenerator);
//	}
//	
//private:
//	Ull				key_;
//	const char*		plainTextFilename_;
//	const char*		encryptedDataFilename_;
//	unsigned char*	plainDataAddr;
//	Ull*			encryptedDataAddr;
//	size_t			sizeOfData;
//	size_t			numberOfBlocks;
//	DesEncryption*	desEncryptor;
//	
//	void createEmptyFile(const char* filename, size_t size) {
//		std::ofstream file;
//		file.open(filename, ios_base::binary);
//		file.seekp(size - 1, 0);
//		file << '\0';
//		file.close();
//	}
//	mapped_region mapFile(const char* filename) {
//		file_mapping mappedFile(filename, read_write);
//		return mapped_region(mappedFile, read_write);
//	}
//	void encryptBlocks() {
//		bitset<sizeOfBlock*bitsInByte>	plainDataBitsetUnit,
//										encryptedDataBitsetUnit;
//
//		for (size_t i = 0; i < numberOfBlocks; i++)
//		{
//			for (size_t j = 0; j < sizeOfBlock; j++)
//			{
//				plainDataBitsetUnit |= (static_cast<Ull>(plainDataAddr[i * bitsInByte + j]) << (j * bitsInByte));
//			}
//			encryptedDataBitsetUnit = desEncryptor->encrypt(plainDataBitsetUnit);
//			encryptedDataAddr[i] = encryptedDataBitsetUnit.to_ullong();
//			plainDataBitsetUnit = 0;
//		}
//	}
//};
//class DesDecryptionFile
//{
//public:
//	DesDecryptionFile(unsigned long long key) : key_(key){}
//	void decryptFile(const char* encryptedTextFilename) {
//		encryptedTextFilename_ = encryptedTextFilename;
//		file_mapping mappedEncryptedText(encryptedTextFilename_, read_write);
//		auto encryptedTextRegion = mapped_region(mappedEncryptedText, read_write);
//		encryptedTextAddr = static_cast<unsigned char*>(encryptedTextRegion.get_address());
//		encryptedTextSize = encryptedTextRegion.get_size();
//
//		createEmptyFile(decryptedTextFilename_, encryptedTextSize);
//
//		file_mapping mappedDecryptedText(decryptedTextFilename_, read_write);
//		auto decryptedTextRegion = mapped_region(mappedDecryptedText, read_write);
//		unsigned long long* decryptedTextAddr = static_cast<unsigned long long*>(decryptedTextRegion.get_address());
//		size_t decryptedSize = static_cast<size_t>(ceil(double(encryptedTextSize) / 8));//overload
//
//
//		unsigned long long encryptedTextUnit = 0;
//		
//		DesDecryption d(key_, roundKeyGenerator_);
//		bitset<64> decryptedTextBitsetUnit, encryptedTextBitsetUnit;
//
//		for (size_t i = 0; i < decryptedSize; i++)
//		{
//			for (size_t j = 0; j < 8; j++)
//			{
//				encryptedTextUnit |= (unsigned long long(encryptedTextAddr[i * 8 + j]) << (j * 8));
//			}
//			//cout << hex << i << " encryptedTextUnit: " << encryptedTextUnit << endl;
//			encryptedTextBitsetUnit = encryptedTextUnit;
//			decryptedTextBitsetUnit = d.decrypt(encryptedTextBitsetUnit);
//			decryptedTextAddr[i] = decryptedTextBitsetUnit.to_ullong();
//			//cout << hex << i << " decryptedTextUnit: " << decryptedTextAddr[i] << endl << endl;
//			encryptedTextUnit = 0;
//		}
//
//	}
//	void setOutputFile(const char* filename) {
//		decryptedTextFilename_ = filename;
//	}
//	void setRoundKeyGenerator(RoundKeyGenerator* roundKeyGenerator) {
//		roundKeyGenerator_ = roundKeyGenerator;
//	}
//private:
//	unsigned long long key_;
//	const char* encryptedTextFilename_;
//	const char* decryptedTextFilename_;
//	unsigned char* encryptedTextAddr;
//	RoundKeyGenerator* roundKeyGenerator_;
//	size_t encryptedTextSize;
//	void createEmptyFile(const char* filename,size_t size) {
//		std::ofstream FILE_SAVE;
//		FILE_SAVE.open(filename, ios_base::binary);
//		FILE_SAVE.seekp(size - 1, 0);
//		FILE_SAVE << '\0';
//		FILE_SAVE.close();
//	}
//};


int main() {
	setlocale(0, "rus");
	{
		Timer timer(__FUNCTION__);
		try {
			RoundKeyGenerator* roundKeyGenerator = new RoundKeyGenerator;
			unsigned long long key = 0xFFBB09182736CCDD;
			const char* plain = "sample.txt";
			const char* encrypted = "encrypted.dat";
			const char* decrypted = "decrypted.txt";

			DesEncryptionFile enc(key);
			enc.initializeDesEncryption(roundKeyGenerator);
			enc.setOutputFile(encrypted);
			enc.encryptFile(plain);

			DesDecryptionFile dec(key);
			dec.initializeDesDecryption(roundKeyGenerator);
			dec.setOutputFile(decrypted);
			dec.decryptFile(encrypted);

			delete roundKeyGenerator;
		}
		catch (const exception &exc) {
			cout << exc.what() << endl << endl;
		}
	}
	
	system("pause");
	return 0;
}