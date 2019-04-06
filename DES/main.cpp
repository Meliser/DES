#include <iostream>
#include <bitset>
#include <array>
#include "Timer.h"

using namespace std;

const size_t keySize = 64;

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

char s1[64] = { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7,
				0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8,
				4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0,
				15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13 };
char s2[64] = { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10,
				3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5,
				0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15,
				13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9 };
char s3[64] = { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8,
				13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1,
				13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7,
				1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12 };
char s4[64] = { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15,
				13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9,
				10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4,
				3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14 };
char s5[64] = { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9,
				14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6,
				4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14,
				11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3 };
char s6[64] = { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11,
				10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8,
				9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6,
				4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13 };
char s7[64] = { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1,
				13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6,
				1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2,
				6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12 };
char s8[64] = { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7,
				1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2,
				7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8,
				2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11 };

char* s[2] = { s2,s3 };
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
			ci = rightCycleShift(c0, currentShift);//!
			di = rightCycleShift(d0, currentShift);//!
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
			cout << int(s[0][2])<<endl;
			RoundKeyGenerator k;
			bitset<64> new_key(0xAABB09182736CCDD);
			bitset<64> key = reverse(new_key);//!
			k.initializeC0D0(key);
			k.generateRoundKeys(16);
			//bitset<64> raw_data(0x123456ABCD132536);//!
			//left_cycle_shift(raw_data,2);
			//right_cycle_shift(raw_data, 2);
			//bitset<64> before_IP = reverse<64>(raw_data);
			//bitset<64> after_IP = rearrange<64,64>(before_IP,IP);
			
			
		}
		catch (const exception &exc) {
			cout << exc.what() << endl << endl;
		}
	}
	
	system("pause");
	return 0;
}