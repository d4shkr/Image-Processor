#include "grayscale.h"

Color Grayscale::GoGray(const Color& old_color) {
    double res = old_color.r * 0.299 + old_color.g * 0.587 + old_color.b * 0.114;
    return {res, res, res};
}

void Grayscale::Apply(Image &image, std::vector<std::string> parameters) {
    if (parameters.size() != 0) {
        throw ImageProcessorException("invalid number of parameters");
    }
    for (size_t x = 0; x < image.GetWidth(); ++x) {
        for (size_t y = 0; y < image.GetHeight(); ++y) {
            image.SetColor(GoGray(image.GetColor(x, y)), x, y);
        }
    }
}

