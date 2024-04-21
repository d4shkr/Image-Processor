#pragma once

#include "image.h"
#include "base_filter.h"

class Sharpening : public Filter {
public:
    void Apply(Image& image, std::vector<std::string> parameters) override;
private:
    static Color Sharpen(const Image& old_image, ssize_t x, ssize_t y);
};
