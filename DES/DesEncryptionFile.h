#pragma once
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <fstream>
#include "DesEncryptionBlocks.h"

using boost::interprocess::mapped_region;
using boost::interprocess::file_mapping;
using boost::interprocess::read_write;
using std::ios_base;

namespace des {
	class DesEncryptionFile
	{
	public:
		DesEncryptionFile(Ull key) :desEncryptorBlocks_(key)
		{}
		void encryptFile(const char* plainDatatFilename);
		void setOutputFile(const char* filename);

	private:
		const char*		encryptedDataFilename_;
		unsigned char*	plainDataAddr_;
		Ull*	encryptedDataAddr_;
		size_t			sizeOfData_;
		DesEncryptionBlocks desEncryptorBlocks_;

		void createEmptyFile(const char* filename, size_t size);
		mapped_region mapFile(const char* filename);
	};
}
