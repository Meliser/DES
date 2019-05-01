
#include "RoundKeyGenerator.h"
const char RoundKeyGenerator::PC1[56] = { 57, 49, 41, 33, 25, 17, 9, 1,
										58, 50, 42, 34, 26, 18, 10, 2,
										59, 51, 43, 35, 27, 19, 11, 3,
										60, 52, 44, 36, 63, 55, 47, 39,
										31, 23, 15, 7, 62, 54, 46, 38,
										30, 22, 14, 6, 61, 53, 45, 37,
										29, 21, 13, 5, 28, 20, 12, 4 };
const char RoundKeyGenerator::PC2[48] = { 14, 17, 11, 24, 1, 5, 3, 28,
											15, 6, 21, 10, 23, 19, 12, 4,
											26, 8, 16, 7, 27, 20, 13, 2,
											41, 52, 31, 37, 47, 55, 30, 40,
											51, 45, 33, 48, 44, 49, 39, 56,
											34, 53, 46, 42, 50, 36, 29, 32 };

void RoundKeyGenerator::initializeC0D0(const bitset<64> &bits) {
	for (size_t i = 0; i < 28; i++)
	{
		c0[i] = bits[PC1[i] - 1];
		d0[i] = bits[PC1[i + 28] - 1];
	}
}

void RoundKeyGenerator::generateRoundKeys(size_t rounds)
{
	bitset<28> ci(c0);
	bitset<28> di(d0);
	bitset<56> temporaryKey;
	size_t currentShift;
	for (size_t i = 0; i < rounds; i++)
	{
		currentShift = countCurrentShift(i + 1);
		ci = leftCycleShift(ci, currentShift);
		di = leftCycleShift(di, currentShift);
		temporaryKey = combineBitSets(ci, di);
		roundKeys[i] = rearrange<56, 48>(temporaryKey, PC2);
	}
	
}

size_t RoundKeyGenerator::countCurrentShift(size_t round)
{
	if (round == 1 or round == 2 or round == 9 or round == 16) {
		return 1;
	}
	else {
		return 2;
	}
}
