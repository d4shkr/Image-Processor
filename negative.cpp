
#include "negative.h"

void Negative::Apply(Image &image, std::vector<std::string> parameters) {
    if (parameters.size() != 0) {
        throw ImageProcessorException("invalid number of parameters");
    }
    for (size_t x = 0; x < image.GetWidth(); ++x) {
        for (size_t y = 0; y < image.GetHeight(); ++y) {
            image.SetColor(Color{1, 1, 1} - (image.GetColor(x, y)), x, y);
        }
    }
}
