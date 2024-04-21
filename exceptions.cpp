#include "exceptions.h"

ImageProcessorException::ImageProcessorException(const std::string& error_message) {
    error_message_ = error_message;
}

ImageProcessorException::ImageProcessorException(const ImageProcessorException &e) {
    error_message_ = e.error_message_;
}

const std::string &ImageProcessorException::GetMessage() const {
    return error_message_;
}
