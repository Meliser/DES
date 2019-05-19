#pragma once
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <fstream>
#include "DesEncryptionBlocks.h"
#include "badFilenameException.h"

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
		void encryptFile(const char* plainDatatFilename, const char* encryptedDataFilename);
		
	private:
		const unsigned char*	plainDataAddr_;
		Ull*	encryptedDataAddr_;
		size_t			sizeOfData_;
		DesEncryptionBlocks desEncryptorBlocks_;
		mapped_region plainDataRegion_;
		mapped_region encryptedDataRegion_;

		void createEmptyFile(const char* filename, size_t size);
		mapped_region mapFile(const char* filename);
	};
}
