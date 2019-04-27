#include <iostream>
#include <bitset>
#include <array>
#include "Timer.h"
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <fstream>
#include <string>
#include <cmath>
#include "DesEncryption.h"
#include "DesDecryption.h"

using namespace std;
using namespace boost::interprocess;

class DesEncryptionFile
{
public:
	DesEncryptionFile(unsigned long long key):key_(key){}
	void encryptFile(const char* plainTextFilename) {
		file_mapping mappedPlainText(plainTextFilename, read_write);
		auto plainTextRegion = mapped_region(mappedPlainText, read_write);
		plainTextAddr = static_cast<unsigned char*>(plainTextRegion.get_address());
		plainTextSize = plainTextRegion.get_size();

		//const char* encryptedFilename = "encrypted.dat";
		std::ofstream FILE_SAVE;
		FILE_SAVE.open(encryptedFilename_, ios_base::binary);
		FILE_SAVE.seekp(plainTextSize - 1, 0);
		FILE_SAVE << '\0';
		FILE_SAVE.close();

		file_mapping mappedEncryptedText(encryptedFilename_, read_write);
		auto encryptedTextRegion = mapped_region(mappedEncryptedText, read_write);
		unsigned long long* encryptedTextAddr = static_cast<unsigned long long*>(encryptedTextRegion.get_address());
		size_t encryptedSize = static_cast<size_t>(ceil(double(plainTextSize) / 8));//overload 

		unsigned long long plainTextUnit = 0;

		DesEncryption e(key_, roundKeyGenerator_);
		bitset<64> plainTextBitsetUnit, encryptedTextBitsetUnit;

		for (size_t i = 0; i < encryptedSize; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				plainTextUnit |= (unsigned long long(plainTextAddr[i * 8 + j]) << (j * 8));
			}
			//cout << hex << i << " plainTextUnit: " << plainTextUnit << endl;
			plainTextBitsetUnit = plainTextUnit;
			encryptedTextBitsetUnit = e.encrypt(plainTextBitsetUnit);
			encryptedTextAddr[i] = encryptedTextBitsetUnit.to_ullong();
			//cout << hex << i << " encryptedTextUnit: " << encryptedTextAddr[i] << endl<<endl;
			plainTextUnit = 0;
		}

	}
	void setRoundKeyGenerator(RoundKeyGenerator* roundKeyGenerator) {
		roundKeyGenerator_ = roundKeyGenerator;
	}
	void setOutputFile(const char* filename) {
		encryptedFilename_ = filename;
	}

private:
	unsigned long long key_;
	const char* plainTextFilename_;
	const char* encryptedFilename_;
	unsigned char* plainTextAddr;
	size_t plainTextSize;
	RoundKeyGenerator* roundKeyGenerator_;
};
class DesDecryptionFile
{
public:
	DesDecryptionFile(unsigned long long key) : key_(key){}
	void decryptFile(const char* encryptedTextFilename) {
		encryptedTextFilename_ = encryptedTextFilename;
		file_mapping mappedEncryptedText(encryptedTextFilename_, read_write);
		auto encryptedTextRegion = mapped_region(mappedEncryptedText, read_write);
		encryptedTextAddr = static_cast<unsigned char*>(encryptedTextRegion.get_address());
		encryptedTextSize = encryptedTextRegion.get_size();

		createEmptyFile(decryptedTextFilename_, encryptedTextSize);

		file_mapping mappedDecryptedText(decryptedTextFilename_, read_write);
		auto decryptedTextRegion = mapped_region(mappedDecryptedText, read_write);
		unsigned long long* decryptedTextAddr = static_cast<unsigned long long*>(decryptedTextRegion.get_address());
		size_t decryptedSize = static_cast<size_t>(ceil(double(encryptedTextSize) / 8));//overload


		unsigned long long encryptedTextUnit = 0;
		
		DesDecryption d(key_, roundKeyGenerator_);
		bitset<64> decryptedTextBitsetUnit, encryptedTextBitsetUnit;

		for (size_t i = 0; i < decryptedSize; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				encryptedTextUnit |= (unsigned long long(encryptedTextAddr[i * 8 + j]) << (j * 8));
			}
			//cout << hex << i << " encryptedTextUnit: " << encryptedTextUnit << endl;
			encryptedTextBitsetUnit = encryptedTextUnit;
			decryptedTextBitsetUnit = d.decrypt(encryptedTextBitsetUnit);
			decryptedTextAddr[i] = decryptedTextBitsetUnit.to_ullong();
			//cout << hex << i << " decryptedTextUnit: " << decryptedTextAddr[i] << endl << endl;
			encryptedTextUnit = 0;
		}

	}
	void setOutputFile(const char* filename) {
		decryptedTextFilename_ = filename;
	}
	void setRoundKeyGenerator(RoundKeyGenerator* roundKeyGenerator) {
		roundKeyGenerator_ = roundKeyGenerator;
	}
private:
	unsigned long long key_;
	const char* encryptedTextFilename_;
	const char* decryptedTextFilename_;
	unsigned char* encryptedTextAddr;
	RoundKeyGenerator* roundKeyGenerator_;
	size_t encryptedTextSize;
	void createEmptyFile(const char* filename,size_t size) {
		std::ofstream FILE_SAVE;
		FILE_SAVE.open(filename, ios_base::binary);
		FILE_SAVE.seekp(size - 1, 0);
		FILE_SAVE << '\0';
		FILE_SAVE.close();
	}
};


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
			enc.setRoundKeyGenerator(roundKeyGenerator);
			enc.setOutputFile(encrypted);
			enc.encryptFile(plain);

			
			DesDecryptionFile dec(key);
			dec.setRoundKeyGenerator(roundKeyGenerator);
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