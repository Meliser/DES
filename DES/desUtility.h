#pragma once
#include <bitset>

using namespace std;

const size_t keySize = 64;
const char IP[64] = { 58,	50,	42,	34,	26,	18,	10,	2,
						  60,	52,	44,	36,	28,	20,	12,	4,
						  62,	54,	46,	38,	30,	22,	14,	6,
						  64,	56,	48,	40,	32,	24,	16,	8,
						  57,	49,	41,	33,	25,	17,	9,	1,
						  59,	51,	43,	35,	27,	19,	11,	3,
						  61,	53,	45,	37,	29,	21,	13,	5,
						  63,	55,	47,	39,	31,	23,	15,	7 };
const char FP[64] = { 40,	8,	48,	16,	56,	24,	64,	32,
				  39,	7,	47,	15,	55,	23,	63,	31,
				  38,	6,	46,	14,	54,	22,	62,	30,
				  37,	5,	45,	13,	53,	21,	61,	29,
				  36,	4,	44,	12,	52,	20,	60,	28,
				  35,	3,	43,	11,	51,	19,	59,	27,
				  34,	2,	42,	10,	50,	18,	58,	26,
				  33,	1,	41,	9,	49,	17,	57,	25 };

//template<size_t bitsSize>
//bitset<bitsSize> reverse(bitset<bitsSize> &bits) {
//	bitset<bitsSize> reversed_bits;
//	bitset<bitsSize> one(1);
//	for (size_t i = 0; i < bitsSize; i++) {
//		reversed_bits |= (((bits >> i) & one) << (bitsSize - 1 - i));
//	}
//	return reversed_bits;
//}

template<size_t bitsSize, size_t tableSize >
bitset<tableSize> rearrange(const bitset<bitsSize> &bits, const char table[]) {
	bitset<tableSize> after_IP;
	for (size_t i = 0; i < tableSize; i++)
	{
		after_IP[i] = bits[table[i]-1];
	}
	return after_IP;
}

template<size_t bitsSize>
bitset<bitsSize> leftCycleShift(bitset<bitsSize> bits, size_t shift) {
	bool headBit;
	for (size_t i = 0; i < shift; i++)
	{
		headBit = bits[bitsSize - 1];
		bits <<= 1;
		bits[0] = headBit;
	}
	return bits;
}

template<size_t bitsSize>
bitset<bitsSize> rightCycleShift(bitset<bitsSize> bits, size_t shift) {
	bool tailBit;
	for (size_t i = 0; i < shift; i++)
	{
		tailBit = bits[0];
		bits >>= 1;
		bits[bitsSize - 1] = tailBit;
	}
	return bits;
}

template<size_t bitsSize>
bitset<2 * bitsSize> combineBitSets(const bitset<bitsSize> &lowBits, const bitset<bitsSize> &highBits) {
	bitset<2 * bitsSize> combination;
	for (size_t i = 0; i < bitsSize; i++)
	{
		combination[i] = lowBits[i];
		combination[i + bitsSize] = highBits[i];
	}
	return combination;
}

template<size_t bitsSize>
void divideBitSets(bitset<bitsSize / 2> &lowBits, bitset<bitsSize / 2> &highBits, const bitset<bitsSize> &bitsToDivide) {
	for (size_t i = 0; i < bitsSize / 2; i++)
	{
		lowBits[i] = bitsToDivide[i];
		highBits[i] = bitsToDivide[i + bitsSize / 2];
	}
}


