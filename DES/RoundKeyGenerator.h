#pragma once
#include <bitset>
#include <array>
#include "desUtility.h"
using namespace std;

class RoundKeyGenerator {
public:
	void initializeC0D0(const bitset<64> &bits);
	void generateRoundKeys(size_t rounds);
	const bitset<48>& getRoundKey(size_t index) const {
		return roundKeys[index];
	}
private:
	const static char PC1[56];
	const static char PC2[48];
	bitset<28> c0;
	bitset<28> d0;
	array<bitset<48>, 16> roundKeys;
	size_t countCurrentShift(size_t round);
};
