#include "gaussian_blur.h"
#include <cmath>

void Blur::Apply(Image& image, std::vector<std::string> parameters) {
    double abs_sigma = std::abs(std::stod(parameters[0]));

    const ssize_t delta = std::ceil(3. * abs_sigma);
    std::vector<double> coefficients;
    for (ssize_t i = 0; i < 2 * delta + 1; ++i) {
        coefficients.push_back(exp(-static_cast<double>((i - delta) * (i - delta)) / (2 * (abs_sigma * abs_sigma))));
    }
    std::vector<double> sums_of_vector;
    double cur_sum = 0;
    for (size_t i = 0; i < delta; ++i) {
        cur_sum += coefficients[i];
    }
    for (size_t i = delta; i < 2 * delta + 1; ++i) {
        cur_sum += coefficients[i];
        sums_of_vector.push_back(cur_sum);
    }

    {
        Image image_copy = Image(image);
        for (ssize_t x = 0; x < image.GetWidth(); ++x) {
            for (ssize_t y = 0; y < image.GetHeight(); ++y) {
                Color col;
                for (ssize_t i = std::max(static_cast<ssize_t>(0), x - delta);
                     i < std::min(static_cast<ssize_t>(image.GetWidth()) - 1, x + delta); ++i) {
                    col += image.GetColor(i, y) * coefficients[i - x + delta];
                }
                col =
                        col / sums_of_vector[std::min(std::min(delta, x), static_cast<ssize_t>(image.GetWidth()) - 1 - x)];
                col.Clamp();
                image.SetColor(col, x, y);
            }
        }
    }
    Image image_copy(image);
    for (ssize_t x = 0; x < image.GetWidth(); ++x) {
        for (ssize_t y = 0; y < image.GetHeight(); ++y) {
            Color col;
            for (ssize_t i = std::max(static_cast<ssize_t>(0), y - delta);
                 i < std::min(static_cast<ssize_t>(image.GetHeight()) - 1, y + delta); ++i) {
                col += image.GetColor(x, i) * coefficients[i - y + delta];
            }
            col = col / sums_of_vector[std::min(std::min(delta, y), static_cast<ssize_t>(image.GetHeight()) - 1 - y)];
            col.Clamp();
            image.SetColor(col, x, y);
        }
    }
}
