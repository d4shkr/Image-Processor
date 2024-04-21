#include <iostream>
#include <unordered_map>
#include <memory>

#include "image.h"
#include "base_filter.h"
#include "grayscale.h"
#include "negative.h"
#include "sharpening.h"
#include "crop.h"
#include "edge.h"
#include "gaussian_blur.h"
#include "palette.h"


int main(int argc, char *argv[]) try {
    if (argc < 2) {
        throw ImageProcessorException("no input path");
    } else if (argc < 3) {
        throw ImageProcessorException("no output path");
    }
    char *input_file_path = argv[1];
    char *output_file_path = argv[2];
    Image my_image(input_file_path);

    /*for (size_t x = 0; x < my_image.GetWidth(); ++x) {
        for (size_t y = 0; y < my_image.GetHeight(); ++y) {
            auto c = my_image.GetColor(y, x);
            std::cout<<'('<<c.r<<','<<c.g<<','<<c.b<<')'<<' ';
        }
        std::cout<<'\n';
    } std::cout<<"\n\n\n\n\n\n\n\n\n\n";*/


    const std::unordered_map<std::string, std::shared_ptr<Filter>>
            filters({{"-gs",    std::make_shared<Grayscale>()},
                     {"-neg",   std::make_shared<Negative>()},
                     {"-sharp", std::make_shared<Sharpening>()},
                     {"-crop",  std::make_shared<Crop>()},
                     {"-edge",  std::make_shared<Edge>()},
                     {"-blur", std::make_shared<Blur>()},
                     {"-pal", std::make_shared<Palette>()}});
    std::vector<std::string> parameters;
    Filter *filter = nullptr;
    try {
        filter = filters.at(argv[3]).get();
    } catch (const std::exception &e) {
        throw ImageProcessorException("invalid filter name");
    }
    for (int it = 4; it < argc; ++it) {
        if (argv[it][0] == '-') {
            filter->Apply(my_image, parameters);
            parameters.clear();
            try {
                filter = filters.at(argv[it]).get();
            } catch (const std::exception &e) {
                throw ImageProcessorException("invalid filter name");
            }
        } else {
            parameters.emplace_back(argv[it]);
        }
    }
    filter->Apply(my_image, parameters);


    /*for (size_t x = 0; x < my_image.GetWidth(); ++x) {
        for (size_t y = 0; y < my_image.GetHeight(); ++y) {
            auto c = my_image.GetColor(y, x);
            std::cout<<'('<<c.r<<','<<c.g<<','<<c.b<<')'<<' ';
        }
        std::cout<<'\n';
    }*/

    my_image.Export(output_file_path);
} catch (const ImageProcessorException &e) {
    std::cout << e.GetMessage();
} catch (const std::exception &e) {
    std::cout << "error";
}

