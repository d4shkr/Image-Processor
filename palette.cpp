#include "palette.h"

#include <algorithm>

Color Palette::FindClosest(const Color& color, const std::vector<Color>& palette) {
    return *std::min_element(palette.begin(), palette.end(), [&color](const Color& a, const Color& b) {
        const double half = .5;
        double r_mean_a = half * (color.r + a.r);
        double r_mean_b = half * (color.r + b.r);
        return (2 + r_mean_a) * (color.r - a.r) * (color.r - a.r) + 4 * (color.g - a.g) * (color.g - a.g) +
               (3 - r_mean_a) * (color.b - a.b) * (color.b - a.b) <
               (2 + r_mean_b) * (color.r - b.r) * (color.r - b.r) + 4 * (color.g - b.g) * (color.g - b.g) +
               (3 - r_mean_b) * (color.b - b.b) * (color.b - b.b);
    });
}
void Palette::Apply(Image& image, std::vector<std::string> parameters) {
    if (parameters.empty()) {
        throw ImageProcessorException("invalid number of parameters");
    }
    std::vector<Color> palette;
    const double max_color_value = 255.;
    try {
        for (const std::string& p : parameters) {
            palette.push_back(Color(std::stod(p.substr(0, 3)) / max_color_value,
                                    std::stod(p.substr(4, 3)) / max_color_value,
                                    std::stod(p.substr(4 * 2, 3)) / max_color_value));
        }
    } catch (std::exception& e) {
        throw ImageProcessorException("invalid parameter format");
    }
    for (ssize_t x = 0; x < image.GetWidth(); ++x) {
        for (ssize_t y = 0; y < image.GetHeight(); ++y) {
            image.SetColor(FindClosest(image.GetColor(x, y), palette), x, y);
        }
    }
}
