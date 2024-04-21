#include "sharpening.h"

Color Sharpening::Sharpen(const Image &old_image, ssize_t x, ssize_t y) {
    const std::vector<std::vector<double>> matrix {{0., -1., 0.}, {-1., 5., -1.}, {0., -1., 0.}};
    Color tmp_color;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            tmp_color += old_image.GetColor(x + i, y + j) * matrix[i + 1][j + 1];
        }
    }
    tmp_color.Clamp();
    return tmp_color;
}

void Sharpening::Apply(Image &image, std::vector<std::string> parameters) {
    if (parameters.size() != 0) {
        throw ImageProcessorException("invalid number of parameters");
    }
    Image image_copy(image);
    for (size_t x = 0; x < image.GetWidth(); ++x) {
        for (size_t y = 0; y < image.GetHeight(); ++y) {
            image.SetColor(Sharpen(image_copy, x, y), x, y);
        }
    }
}
