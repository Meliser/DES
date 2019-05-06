#include <iostream>
#include "DesEncryptionFile.h"
#include "DesDecryptionFile.h"

using std::cout;
using std::endl;
using std::exception;
using des::DesEncryptionFile;
using des::DesDecryptionFile;

int main() {
	setlocale(0, "rus");
	{
		try {
			unsigned long long key = 0xAA182736CCee;
			const char* plain =		"sample.txt";
			const char* encrypted = "encrypted.dat";
			const char* decrypted = "decrypted.txt";
			
			DesEncryptionFile enc(key);
			enc.setOutputFile(encrypted);
			enc.encryptFile(plain);

			DesDecryptionFile dec(key);
			dec.setOutputFile(decrypted);
			dec.decryptFile(encrypted);

		}
		catch (const exception &exc) {
			cout << exc.what() << endl << endl;
		}

	}
	
	system("pause");
	return 0;
}