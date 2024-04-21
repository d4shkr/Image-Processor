#pragma once

#include "image.h"
#include "base_filter.h"

class Negative : public Filter {
public:
    void Apply(Image& image, std::vector<std::string> parameters) override;
};