#include "badFilenameException.h"

des::badFilenameException::badFilenameException(string message):message_("Invalid filename or path to file: ") {
		message_ += message;
}
const char* des::badFilenameException::what()const noexcept {
	return message_.c_str();
}