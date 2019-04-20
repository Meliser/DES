#include <iostream>
#include <bitset>
#include <array>
#include "Timer.h"
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include <fstream>
#include <string>
//#include "desUtility.h"
#include "DesEncryption.h"
#include "DesDecryption.h"
//#include "feistelFunction.h"
//#include "RoundKeyGenerator.h"
using namespace std;






using  namespace boost::interprocess;
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
			
			RoundKeyGenerator roundKeyGenerator;
			DesEncryption e(0xAABB09182736CCDD,&roundKeyGenerator);
			bitset<64> plain(0x123456ABCD132536);//0x123456ABCD132536
			e.encrypt(plain);

			DesDecryption d(0xAABB09182736CCDD,&roundKeyGenerator);
			bitset<64> cipher(0x815ecdae889d1add);
			d.decrypt(cipher);
			
		}
		catch (const exception &exc) {
			cout << exc.what() << endl << endl;
		}
	}
	
	system("pause");
	return 0;
}