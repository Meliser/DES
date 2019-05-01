#include "desUtility.h"

template<size_t bitsSize, size_t tableSize >
bitset<tableSize> rearrange(const bitset<bitsSize> &bits, const char table[]) {
	bitset<tableSize> after_IP;
	for (size_t i = 0; i < tableSize; i++)
	{
		after_IP[i] = bits[table[i] - 1];
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


