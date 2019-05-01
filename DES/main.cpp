#include <iostream>
#include "Timer.h"
#include "DesEncryptionFile.h"
#include "DesDecryptionFile.h"


using namespace std;
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