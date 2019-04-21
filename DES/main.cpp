#include <iostream>
#include <bitset>
#include <array>
#include "Timer.h"
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <fstream>
#include <string>
#include "DesEncryption.h"
#include "DesDecryption.h"

using namespace std;
using namespace boost::interprocess;

class DesEncryptionFile
{
public:
	DesEncryptionFile(const char* plainTextFilename):plainTextFilename_(plainTextFilename){
		file_mapping mappedPlainText(plainTextFilename_, read_write);
		auto plainTextRegion = new mapped_region(mappedPlainText, read_write);
		plainTextAddr = static_cast<unsigned char*>(plainTextRegion->get_address());
		plainTextSize = plainTextRegion->get_size();

		const char* encryptedFilename = "encrypted.dat";
		std::ofstream FILE_SAVE;
		FILE_SAVE.open(encryptedFilename,ios_base::binary);
		FILE_SAVE.seekp(plainTextSize-1, 0);
		FILE_SAVE << '\0';
		FILE_SAVE.close();

		file_mapping mappedEncryptedText(encryptedFilename, read_write);
		auto encryptedTextRegion = new mapped_region(mappedEncryptedText, read_write);
		unsigned long long* encryptedTextAddr = static_cast<unsigned long long*>(encryptedTextRegion->get_address());
		size_t encryptedSize = plainTextSize/8;//!!!!

		unsigned long long plainTextUnit = 0;
		RoundKeyGenerator roundKeyGenerator;
		DesEncryption e(0xAABB09182736CCDD, &roundKeyGenerator);
		bitset<64> plainTextBitsetUnit,encryptedTextBitsetUnit;

		for (size_t i = 0; i < encryptedSize; i++)
		{
			for (size_t j = 0;  j < 8;  j++)
			{
				plainTextUnit |= (unsigned long long(plainTextAddr[i*8+j]) << (j * 8));
			}
			cout << hex << i << " plainTextUnit: " << plainTextUnit << endl;
			plainTextBitsetUnit = plainTextUnit;
			encryptedTextBitsetUnit = e.encrypt(plainTextBitsetUnit);
			encryptedTextAddr[i] = encryptedTextBitsetUnit.to_ullong();
			cout << hex << i << " encryptedTextUnit: " << encryptedTextAddr[i] << endl<<endl;
			plainTextUnit = 0;
		}

		
		//DesEncryption e(0xAABB09182736CCDD,&roundKeyGenerator);//0xAABB09182736CCDD
		//array<bitset<64>, 5> dat;
		//for (size_t i = 0; i < 5; i++)
		//{
		//	//cout << hex << arr[i] << endl;
		//	bitset<64> plain(arr[i]);//0x123456ABCD132536
		//	encryptedAddr[i] = e.encrypt(plain).to_ullong();
		//}

		/*DesDecryption d(0xAABB09182736CCDD,&roundKeyGenerator);
		array<bitset<64>, 5> dat1;
		for (size_t i = 0; i < 5; i++)
		{
			dat1[i] = bitset<64>(encryptedAddr[i]);
		}
		
		for (size_t i = 0; i < 5; i++)
		{
			dat1[i] = d.decrypt(dat1[i]);
		}
		cout << endl;
		for (size_t i = 0; i < 5; i++)
		{
			cout  << dat1[i].to_ullong() << endl;
		}*/
	}
	

private:
	const char* plainTextFilename_;
	unsigned char* plainTextAddr;
	size_t plainTextSize;
};
class DesDecryptionFile
{
public:
	DesDecryptionFile(const char* encryptedTextFilename) : encryptedTextFilename_(encryptedTextFilename) {
		file_mapping mappedEncryptedText(encryptedTextFilename_, read_write);
		auto encryptedTextRegion = new mapped_region(mappedEncryptedText, read_write);
		encryptedTextAddr = static_cast<unsigned char*>(encryptedTextRegion->get_address());
		encryptedTextSize = encryptedTextRegion->get_size();

		const char* decryptedFilename = "decrypted.dat";
		std::ofstream FILE_SAVE;
		FILE_SAVE.open(decryptedFilename, ios_base::binary);
		FILE_SAVE.seekp(encryptedTextSize - 1, 0);
		FILE_SAVE << '\0';
		FILE_SAVE.close();

		file_mapping mappedDecryptedText(decryptedFilename, read_write);
		auto decryptedTextRegion = new mapped_region(mappedDecryptedText, read_write);
		unsigned long long* decryptedTextAddr = static_cast<unsigned long long*>(decryptedTextRegion->get_address());
		size_t decryptedSize = encryptedTextSize / 8;//!!!!

		unsigned long long encryptedTextUnit = 0;
		RoundKeyGenerator roundKeyGenerator;
		DesDecryption d(0xAABB09182736CCDD, &roundKeyGenerator);
		bitset<64> decryptedTextBitsetUnit, encryptedTextBitsetUnit;

		for (size_t i = 0; i < decryptedSize; i++)
		{
			for (size_t j = 0; j < 8; j++)
			{
				encryptedTextUnit |= (unsigned long long(encryptedTextAddr[i * 8 + j]) << (j * 8));
			}
			cout << hex << i << " encryptedTextUnit: " << encryptedTextUnit << endl;
			encryptedTextBitsetUnit = encryptedTextUnit;
			decryptedTextBitsetUnit = d.decrypt(encryptedTextBitsetUnit);
			decryptedTextAddr[i] = decryptedTextBitsetUnit.to_ullong();
			cout << hex << i << " decryptedTextUnit: " << decryptedTextAddr[i] << endl << endl;
			encryptedTextUnit = 0;
		}
	}
	

private:
	const char* encryptedTextFilename_;
	unsigned char* encryptedTextAddr;
	size_t encryptedTextSize;
};


int main() {
	setlocale(0, "rus");
	{
		Timer timer(__FUNCTION__);
		try {
			/*std::ofstream FILE_SAVE;
			FILE_SAVE.open("ddddd.dat",ios_base::binary);
			FILE_SAVE.seekp(32, 0);
			FILE_SAVE << '\0';
			FILE_SAVE.close();*/
			
			//const char* filename = "ddddd.dat";// ddddd.dat plainText.txt
			//file_mapping m_data(filename, read_write);//access rights
			//auto region = new mapped_region(m_data, read_write);

			//auto data_addr = static_cast<unsigned char*/*unsigned long long**/>(region->get_address());
			//
			//using ull = unsigned long long;
			//size_t data_size = region->get_size();
			//size_t size = data_size / sizeof(ull);
			//unsigned long long arr[5] = {0,0,0,0,0};
			//size_t current,offset;
			//
			//for (size_t i = 0; i < data_size; i++)
			//{
			//	current = i / sizeof(unsigned long long);
			//	offset = i % sizeof(unsigned long long);
			//	arr[current] |= (unsigned long long(data_addr[i]) << (offset * 8));
			//	
			//	//data_addr[i]=i;
			//}
			//for (size_t i = 0; i < 5; i++)
			//{
			//	cout << hex << arr[i] << endl;
			//}
			
			//RoundKeyGenerator roundKeyGenerator;
			//DesEncryption e(0xAABB09182736CCDD,&roundKeyGenerator);//0xAABB09182736CCDD
			//bitset<64> plain(0x706050403020100);//0x123456ABCD132536
			//e.encrypt(plain);

			//DesDecryption d(0xAABB09182736CCDD,&roundKeyGenerator);
			//bitset<64> cipher(0x67aae679b5d08559);
			//d.decrypt(cipher);

			//const char* plain = "plainText.dat";
			//DesEncryptionFile enc(plain);
			const char* encrypted = "encrypted.dat";
			DesDecryptionFile dec(encrypted);
			
		}
		catch (const exception &exc) {
			cout << exc.what() << endl << endl;
		}
	}
	
	system("pause");
	return 0;
}