#include <iostream>
#include "DesEncryptionFile.h"
#include "DesDecryptionFile.h"
#include "DesEncryptionString.h"
#include "DesDecryptionString.h"
#include "badFilenameException.h"
#include <string>

using std::cout;
using std::endl;
using std::exception;
using des::DesEncryptionFile;
using des::DesDecryptionFile;
using des::DesEncryptionBlocks;
using des::DesDecryptionBlocks;
using des::DesEncryptionString;
using des::DesDecryptionString;
using std::string;

int main() {
	setlocale(0, "rus");
	{
		try {
			unsigned long long key = 0xff;
			const char* plain =		"C:\\Users\\Meliser\\source\\repos\\DES\\DES\\sample.txt";
			const char* encrypted = "C:\\Users\\Meliser\\source\\repos\\DES\\DES\\encrypted.dat";
			const char* decrypted = "C:\\Users\\Meliser\\source\\repos\\DES\\DES\\decrypted.txt";
			
			DesEncryptionFile enc(key);
			enc.encryptFile(plain,encrypted);
			
			DesDecryptionFile dec(key);
			dec.decryptFile(encrypted, decrypted);

			DesEncryptionString encS(key);
			string pstring("hellotraèèèèèèèÈ");
			encS.encryptString(pstring);
			cout << encS.getAccumulator()<<"|"<< endl;

			DesDecryptionString decS(key);
		
			string es(encS.getAccumulator());
			decS.decryptString(es);
			cout << decS.getAccumulator()<< "|" << endl;
			
		}
		catch (const exception &exception) {
			cout << exception.what() << endl << endl;
		}

	}
	
	system("pause");
	return 0;
}