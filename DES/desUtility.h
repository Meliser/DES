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


template<size_t bitsSize, size_t tableSize >
bitset<tableSize> rearrange(const bitset<bitsSize> &bits, const char table[]);
template bitset<32> rearrange(const bitset<32> &bits, const char table[]);
template bitset<64> rearrange(const bitset<64> &bits, const char table[]);
template bitset<48> rearrange(const bitset<32> &bits, const char table[]);
template bitset<48> rearrange(const bitset<56> &bits, const char table[]);

template<size_t bitsSize>
bitset<bitsSize> leftCycleShift(bitset<bitsSize> bits, size_t shift);
template bitset<28> leftCycleShift(bitset<28> bits, size_t shift);

template<size_t bitsSize>
bitset<bitsSize> rightCycleShift(bitset<bitsSize> bits, size_t shift);

template<size_t bitsSize>
bitset<2 * bitsSize> combineBitSets(const bitset<bitsSize> &lowBits, const bitset<bitsSize> &highBits);
template bitset<56> combineBitSets(const bitset<28> &lowBits, const bitset<28> &highBits);
template bitset<64> combineBitSets(const bitset<32> &lowBits, const bitset<32> &highBits);

template<size_t bitsSize>
void divideBitSets(bitset<bitsSize / 2> &lowBits, bitset<bitsSize / 2> &highBits, const bitset<bitsSize> &bitsToDivide);
template void divideBitSets(bitset<32> &lowBits, bitset<32> &highBits, const bitset<64> &bitsToDivide);

//#include "desUtility.cpp"
