#pragma once
#include "RoundKeyGenerator.h"
#include "feistelFunction.h"

using std::bitset;
namespace des {
	class DesDecryption {
	public:
		DesDecryption(Ull key);
		~DesDecryption();
		bitset<blockSize> decrypt(bitset<blockSize> &cipherText);
	private:
		bitset<keySize> key_;
		RoundKeyGenerator *roundKeyGenerator_;
		bitset<blockSize/2> lPart_;
		bitset<blockSize/2> rPart_;
	};
}
