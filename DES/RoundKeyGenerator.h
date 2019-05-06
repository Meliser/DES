#pragma once
#include <bitset>
#include <array>
#include "desUtility.h"

using std::bitset;
using std::array;

namespace des {
	class RoundKeyGenerator {
	public:
		void initializeC0D0(const bitset<keySize> &bits);
		void generateRoundKeys(size_t rounds);
		const bitset<roundKeySize>& getRoundKey(size_t index) const {
			return roundKeys[index];
		}
	private:
		const static char PC1[PC1Size];
		const static char PC2[PC2Size];
		bitset<PC1Size / 2> c0;
		bitset<PC1Size / 2> d0;
		array<bitset<roundKeySize>, rounds> roundKeys;
		size_t countCurrentShift(size_t round);
	};
}

