#pragma once
#include <bitset>
#include "desUtility.h"

using namespace std;
struct Tables {
	static const char E[48];
	static const char P[32];

	static const char s1[64];
	static const char s2[64];
	static const char s3[64];
	static const char s4[64];
	static const char s5[64];
	static const char s6[64];
	static const char s7[64];
	static const char s8[64];
	static const char* sBoxes[8];
};

bitset<32> feistelFunction(const bitset<32> &rPart, const bitset<48> &roundKey);

