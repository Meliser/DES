#include <iostream>
#include <bitset>
#include <array>
#include "Timer.h"

using namespace std;

template<size_t bitsSize>
bitset<bitsSize> reverse(bitset<bitsSize> &bits) {
	bitset<bitsSize> reversed_bits;
	bitset<bitsSize> one(1);
	for (size_t i = 0; i < bitsSize; i++) {
		reversed_bits |= (((bits >> i) & one) << (bitsSize - 1 - i));
	}
	return reversed_bits;
}

template<size_t bitsSize,size_t tableSize >
bitset<tableSize> rearrange(bitset<bitsSize> &bits, char table[]) {
	bitset<tableSize> after_IP;
	char current;
	for (size_t i = 0; i < tableSize; i++)//!
	{
		current = table[i];
		after_IP[i] = bits[--current];
	}
	return after_IP;
}

template<size_t bitsSize>
bitset<bitsSize> leftCycleShift(const bitset<bitsSize> &bits,size_t sbits) {
	bool head_bit;
	bitset<bitsSize> shiftedBits = bits;
	for (size_t i = 0; i < sbits; i++)
	{
		head_bit = shiftedBits[bitsSize - 1];
		shiftedBits <<= 1;
		shiftedBits[0] = head_bit;
	}
	return shiftedBits;
}

template<size_t bitsSize>
bitset<bitsSize> rightCycleShift(bitset<bitsSize> &bits, size_t sbits) {
	bool tail_bit;
	bitset<bitsSize> shiftedBits = bits;
	for (size_t i = 0; i < sbits; i++)
	{
		tail_bit = shiftedBits[0];
		shiftedBits >>= 1;
		shiftedBits[bitsSize-1] = tail_bit;
	}
	return shiftedBits;
}

template<size_t bitsSize>
void show(bitset<bitsSize> &bits) {
	
	for (size_t i = 0; i < bitsSize; i++)
	{
		cout << bits[i] << " ";
	}
	cout << endl;
}

const size_t keySize = 64;
class DesEncryption {
public:
	DesEncryption(unsigned long long key) : key_(key){}
	
private:
	bitset<keySize> key_;
};

class RoundKeyGenerator {
public:
	RoundKeyGenerator():currentShift(0){}
	template<size_t bitsSize>
	void initializeC0D0(bitset<bitsSize> &bits) {
		cout << "c0: ";
		for (size_t i = 0; i < 28; i++)//!
		{
			c0[i] = bits[--roundKeyTable_[i]];
			cout << c0[i] << " ";
		}
		cout << endl;
		cout << "d0: ";
		for (size_t i = 0; i < 28; i++)//!
		{
			d0[i] = bits[--roundKeyTable_[i+28]];
			cout << d0[i] << " ";
		}
		cout << endl << endl;
	}
	void generateRoundKeys(unsigned rounds) {
		for (size_t i = 0; i < rounds; i++)
		{
			countCurrentShift(i+1);
			ci = rightCycleShift(c0, currentShift);
			di = rightCycleShift(d0, currentShift);
			cout << "c" << i+1 << ": ";
			show(ci);
			cout << "d" << i+1 << ": ";
			show(di);
			for (size_t j = 0; j < 28; j++)
			{
				temporaryKey[j] = ci[j];
				temporaryKey[j+28] = di[j];
			}
			cout << "temporaryKey: ";
			show(temporaryKey);
			roundKeys[i] = rearrange<56,48>(temporaryKey, finalTable_);
			cout << "roundKey: ";
			show(roundKeys[i]);
			cout << endl;
		}
	}
private:
	 static char roundKeyTable_[56];
	 static char finalTable_[48];
	 bitset<28> c0;
	 bitset<28> d0;
	 bitset<28> ci;
	 bitset<28> di;
	 bitset<56> temporaryKey;
	 array<bitset<48>, 16> roundKeys;
	 unsigned currentShift;
	 void countCurrentShift(unsigned round) {
		 if (round == 1 or round == 2 or round == 9 or round == 16) {
			 currentShift++;
		 }
		 else {
			 currentShift+=2;
		 }
	 }
};
char RoundKeyGenerator::roundKeyTable_[56] = { 57, 49, 41, 33, 25, 17, 9, 1,
										58, 50, 42, 34, 26, 18, 10, 2,
										59, 51, 43, 35, 27, 19, 11, 3,
										60, 52, 44, 36, 63, 55, 47, 39,
										31, 23, 15, 7, 62, 54, 46, 38,
										30, 22, 14, 6, 61, 53, 45, 37,
										29, 21, 13, 5, 28, 20, 12, 4 };
char RoundKeyGenerator::finalTable_[48] = { 14, 17, 11, 24, 1, 5, 3, 28,
											15, 6, 21, 10, 23, 19, 12, 4,
											26, 8, 16, 7, 27, 20, 13, 2,
											41, 52, 31, 37, 47, 55, 30, 40,
											51, 45, 33, 48, 44, 49, 39, 56,
											34, 53, 46, 42, 50, 36, 29, 32 };
int main() {
	//setlocale(0, "rus");
	{
		Timer timer(__FUNCTION__);
		try {
			const unsigned keyLength = 64;
			const char IP[64] = { 58,	50,	42,	34,	26,	18,	10,	2,
							60,	52,	44,	36,	28,	20,	12,	4,
							62,	54,	46,	38,	30,	22,	14,	6,
							64,	56,	48,	40,	32,	24,	16,	8,
							57,	49,	41,	33,	25,	17,	9,	1,
							59,	51,	43,	35,	27,	19,	11,	3,
							61,	53,	45,	37,	29,	21,	13,	5,
							63,	55,	47,	39,	31,	23,	15,	7 };

			const char P[48] = { 32, 1, 2, 3, 4, 5, 4, 5,
							6, 7, 8, 9, 8, 9, 10, 11,
							12, 13, 12, 13, 14, 15, 16, 17,
							16, 17, 18, 19, 20, 21, 20, 21,
							22, 23, 24, 25, 24, 25, 26, 27,
							28, 29, 28, 29, 30, 31, 32, 1 };

			RoundKeyGenerator k;
			bitset<64> new_key(0xAABB09182736CCDD);
			bitset<64> key = reverse(new_key);
			k.initializeC0D0(key);
			k.generateRoundKeys(16);
			//bitset<64> raw_data(0x123456ABCD132536);//!
			//left_cycle_shift(raw_data,2);
			//right_cycle_shift(raw_data, 2);
			//bitset<64> before_IP = reverse<64>(raw_data);
			//bitset<64> after_IP = rearrange<64,64>(before_IP,IP);
			//bitset<keyLength> key(0xAABB89182736CCDD);
			//bitset<56> new_key = rearrange<keyLength, 56>(key, roundKeyTable);
			/*bitset<28> C0;
			bitset<28> D0;
			for (size_t i = 0; i < 28; i++)
			{
				C0[i] = new_key[i];
				D0[i] = new_key[28+i];
			}
			cout << "C0: ";
			for (size_t i = 0; i < 28; i++)
			{
				cout<<C0[i]<<" ";
			}
			cout << endl;
			cout << "D0: ";
			for (size_t i = 0; i < 28; i++)
			{
				cout << D0[i] << " ";
			}
			cout << endl;*/
		}
		catch (const exception &exc) {
			cout << exc.what() << endl << endl;
		}
	}
	
	system("pause");
	return 0;
}