#pragma once
#include <string>
using std::string;
using std::exception;

namespace des {
	class badFilenameException:public exception
	{
	public:
		badFilenameException(string message);
		const char* what()const noexcept override;
	private:
		string message_;
	};
}