#pragma once
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <fstream>
#include <string>
#include "DesDecryptionBlocks.h"
#include "badFilenameException.h"

using boost::interprocess::mapped_region;
using boost::interprocess::file_mapping;
using boost::interprocess::read_write;
using std::ios_base;

namespace des {
	class DesDecryptionFile
	{
	public:
		DesDecryptionFile(Ull key) :desDecryptorBlocks_(key)
		{}
		void decryptFile(const char* encryptedDatatFilename, const char* decryptedDataFilename);

	private:
		unsigned char*	encryptedDataAddr_;
		Ull*			decryptedDataAddr_;
		size_t			sizeOfData_;
		DesDecryptionBlocks desDecryptorBlocks_;
		mapped_region encryptedDataRegion_;
		mapped_region decryptedDataRegion_;

		void createEmptyFile(const char* filename, size_t size);
		mapped_region mapFile(const char* filename);
	};
}
