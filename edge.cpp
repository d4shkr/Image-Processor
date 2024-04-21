#include "edge.h"

Color Edge::ApplyMatrix(const Image &old_image, ssize_t x, ssize_t y) {
    const std::vector<std::vector<double>> matrix {{0., -1., 0.}, {-1., 4., -1.}, {0., -1., 0.}};
    Color tmp_color;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            tmp_color += old_image.GetColor(x + i, y + j) * matrix[i + 1][j + 1];
        }
    }
    tmp_color.Clamp();
    return tmp_color;
}

void Edge::Apply(Image &image, std::vector<std::string> parameters) {
    if (parameters.size() != 1) {
        throw ImageProcessorException("invalid number of parameters");
    }
    Grayscale().Apply(image, {});
    double threshold = 0.;
    try {
        threshold = std::stod(parameters[0]);
    } catch (const std::exception& e) {
        throw ImageProcessorException("invalid parameter format");
    }
    Image image_copy(image);
    for (size_t x = 0; x < image.GetWidth(); ++x) {
        for (size_t y = 0; y < image.GetHeight(); ++y) {
            if (ApplyMatrix(image_copy, x, y).r > threshold) {
                image.SetColor({1., 1., 1.}, x, y);
            } else {
                image.SetColor({0., 0., 0.}, x, y);
            }
        }
    }
}