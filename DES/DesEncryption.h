#pragma once
#include "RoundKeyGenerator.h"
#include "feistelFunction.h"
using std::bitset;
namespace des {
	class DesEncryption {
	public:
		DesEncryption(Ull key);
		~DesEncryption();
		bitset<blockSize> encrypt(const bitset<blockSize> &plainText);
	private:
		bitset<keySize> key_;
		RoundKeyGenerator *roundKeyGenerator_;
		bitset<blockSize/2> lPart_;
		bitset<blockSize/2> rPart_;
	};
}
