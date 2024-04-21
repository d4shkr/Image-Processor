#pragma once

#include <exception>
#include <string>

class ImageProcessorException : public std::exception {
public:
    explicit ImageProcessorException(const std::string&);
    explicit ImageProcessorException(const ImageProcessorException& e);
    const std::string& GetMessage() const;
private:
    std::string error_message_;
};