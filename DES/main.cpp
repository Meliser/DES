#include <iostream>
#include "DesEncryptionFile.h"
#include "DesDecryptionFile.h"
#include "badFilenameException.h"
using std::cout;
using std::endl;
using std::exception;
using des::DesEncryptionFile;
using des::DesDecryptionFile;

int main() {
	setlocale(0, "rus");
	{
		try {
			unsigned long long key = 0xAA182736CAA;
			const char* plain =		"C:\\Users\\Meliser\\source\\repos\\DES\\DES\\sample.tt";
			const char* encrypted = "C:\\Users\\Meliser\\source\\repos\\DES\\DES\\encrypted.dat";
			const char* decrypted = "C:\\Users\\Meliser\\source\\repos\\DES\\DES\\decrypted.txt";
			
			DesEncryptionFile enc(key);
			enc.encryptFile(plain,encrypted);

			DesDecryptionFile dec(key);
			dec.decryptFile(encrypted, decrypted);

		}
		catch (const exception &exception) {
			cout << exception.what() << endl << endl;
		}

	}
	
	system("pause");
	return 0;
}