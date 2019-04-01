#include <iostream>
#include <bitset>
#include "Timer.h"
using namespace std;
bitset<64> reverse(bitset<64> &bits) {
	bitset<64> reversed_bits;
	bitset<64> one(1);
	for (size_t i = 0; i < 64; ++i) {
		reversed_bits |= (((bits >> i) & one) << (63 - i));
	}
	return reversed_bits;
}
bitset<64> rearrange(bitset<64> &bits, char IP[], size_t size) {
	bitset<64> after_IP;
	for (size_t i = 0; i < size; i++)//!
	{
		after_IP[i] = bits[--IP[i]];
	}
	return after_IP;
}
int main() {
	setlocale(0, "rus");
	{
		Timer timer(__FUNCTION__);
		try {
			bitset<64> before_IP(0b0000000000000010000000000000000000000000000000000000000000000001);//!
			bitset<64> change_IP = reverse(before_IP);
			
			char IP[64] = { 58,	50,	42,	34,	26,	18,	10,	2,
							60,	52,	44,	36,	28,	20,	12,	4,
							62,	54,	46,	38,	30,	22,	14,	6,
							64,	56,	48,	40,	32,	24,	16,	8,
							57,	49,	41,	33,	25,	17,	9,	1,
							59,	51,	43,	35,	27,	19,	11,	3,
							61,	53,	45,	37,	29,	21,	13,	5,
							63,	55,	47,	39,	31,	23,	15,	7 };
			bitset<64> after_IP = rearrange(change_IP,IP,64);
			
		}
		catch (const exception &exc) {
			cout << exc.what() << endl << endl;
		}
	}
	
	system("pause");
	return 0;
}