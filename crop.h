#pragma once

#include "image.h"
#include "base_filter.h"

class Crop : public Filter {
public:
    void Apply(Image& image, std::vector<std::string> parameters) override;
};
