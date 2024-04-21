#include "crop.h"

void Crop::Apply(Image &image, std::vector<std::string> parameters) {
    if (parameters.size() != 2) {
        throw ImageProcessorException("invalid number of parameters");
    }
    try {
        image.Resize(std::stoi(parameters[0]), std::stoi(parameters[1]));
    } catch (const std::exception &e) {
        throw ImageProcessorException("invalid parameter format");
    }
}
