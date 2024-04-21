#pragma once

#include <cmath>

#include "image.h"
#include "base_filter.h"

class Blur : public Filter {
public:
    //~Blur() override = default;
    void Apply(Image& image, std::vector<std::string> parameters) override;
};