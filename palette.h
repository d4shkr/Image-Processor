#pragma once

#include "image.h"
#include "base_filter.h"

class Palette : public Filter {
public:
    void Apply(Image& image, std::vector<std::string> parameters) override;

private:
    static Color FindClosest(const Color&, const std::vector<Color>&);
};
