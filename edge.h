#pragma once

#include "image.h"
#include "base_filter.h"
#include "grayscale.h"

class Edge : public Filter {
public:
    void Apply(Image& image, std::vector<std::string> parameters) override;
private:
    static Color ApplyMatrix(const Image& old_image, ssize_t x, ssize_t y);
};

