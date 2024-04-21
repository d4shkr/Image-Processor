#pragma once

#include "image.h"
#include "base_filter.h"

class Grayscale : public Filter {
public:
    void Apply(Image& image, std::vector<std::string> parameters) override;
private:
    static Color GoGray(const Color& old_color);
};
