#pragma once

#include "image.h"

class Filter {
public:
    virtual void Apply(Image& image, std::vector<std::string> parameters) = 0;
};