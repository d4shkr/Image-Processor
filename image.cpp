
#include "image.h"
#include <iostream>
#include <fstream>

Color::Color() {
    r = 0, g = 0, b = 0;
}

Color::Color(double r_input, double g_input, double b_input) {
    r = r_input, g = g_input, b = b_input;
}


Color::~Color() {

}

Color Color::operator+(const Color &other) const {
    return Color(r + other.r, g + other.g, b + other.b);
}

Color Color::operator-(const Color &other) const {
    return *this + other * -1;
}

Color &Color::operator=(const Color &other) {
    r = other.r;
    g = other.g;
    b = other.b;
    return *this;
}

Color Color::operator*(const double other) const {
    return Color(r * other, g * other, b * other);
}

Color &Color::operator+=(const Color &other) {
    *this = *this + other;
    return *this;
}

void Color::Clamp() {
    r = std::min(1., std::max(0., r));
    g = std::min(1., std::max(0., g));
    b = std::min(1., std::max(0., b));
}


Image::Image(const char *path) {
    Read(path);
}

Image::Image(size_t width, size_t height) {
    width_ = width, height_ = height,
    colors_ = std::vector<std::vector<Color>>(height, std::vector<Color>(width));
}

Image::Image(const Image & old_image) {
    width_ = old_image.width_, height_ = old_image.height_,
    colors_ = old_image.colors_;

}

Color Color::operator/(double other) const {
    return Color(r / other, g / other, b / other);
}

Color Image::GetColor(ssize_t x, ssize_t y) const {
    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }
    if (x >= width_) {
        x = width_ - 1;
    }
    if (y >= height_) {
        y = height_ - 1;
    }
    return colors_[y][x];
}

void Image::SetColor(const Color & color, size_t x, size_t y) {
    colors_[y][x].r = color.r;
    colors_[y][x].g = color.g;
    colors_[y][x].b = color.b;
}

Image::~Image() {
}

void Image::Export(const char *path) {
    const size_t file_header_size = 14;
    const size_t info_header_size = 40;

    std::ofstream file;
    try {
        file.open(path, std::ios::binary);
        if (!file.is_open()) {
            throw ImageProcessorException("can't open the file");
        }

        unsigned char bmp_padding[3] = {0, 0, 0};
        const size_t padding_num = ((4 - (width_ * 3) % 4) % 4);

        const size_t file_size = file_header_size + info_header_size +
                                 width_ * height_ * 3 + padding_num * height_;

        unsigned char file_header[file_header_size];
        file_header[0] = 'B';
        file_header[1] = 'M';

        file_header[2] = file_size;
        file_header[3] = file_size >> 8;
        file_header[4] = file_size >> 16;
        file_header[5] = file_size >> 24;
        for (int i = 6; i < 14; ++i) {
            if (i != 10) {
                file_header[i] = 0;
            } else {
                file_header[i] = file_header_size + info_header_size;
            }
        }

        unsigned char info_header[info_header_size];
        info_header[0] = info_header_size;
        info_header[1] = 0;
        info_header[2] = 0;
        info_header[3] = 0;

        info_header[4] = width_;
        info_header[5] = width_ >> 8;
        info_header[6] = width_ >> 16;
        info_header[7] = width_ >> 24;

        info_header[8] = height_;
        info_header[9] = height_ >> 8;
        info_header[10] = height_ >> 16;
        info_header[11] = height_ >> 24;

        info_header[12] = 1;
        info_header[13] = 0;

        info_header[14] = 24;
        for (int i = 15; i < 40; ++i) {
            info_header[i] = 0;
        }

        file.write(reinterpret_cast<char *>(file_header), file_header_size);
        file.write(reinterpret_cast<char *>(info_header), info_header_size);

        for (size_t y = 0; y < height_; ++y) {
            for (size_t x = 0; x < width_; ++x) {
                unsigned char r = static_cast<unsigned char>(GetColor(x, y).r * 255.0);
                unsigned char g = static_cast<unsigned char>(GetColor(x, y).g * 255.0);
                unsigned char b = static_cast<unsigned char>(GetColor(x, y).b * 255.0);

                unsigned char color[] = {b, g, r};
                file.write(reinterpret_cast<char *>(color), 3);
            }
            file.write(reinterpret_cast<char *>(bmp_padding), padding_num);
        }
        file.close();
    } catch (const ImageProcessorException& e){
        file.close();
        throw ImageProcessorException(e);
    } catch (const std::exception& e) {
        file.close();
        throw ImageProcessorException("file export error");
    }
}

void Image::Read(const char *path) {
    const size_t file_header_size = 14;
    const size_t info_header_size = 40;

    std::ifstream file;
    try {
        file.open(path, std::ios::binary);
        if (!file.is_open()) {
            throw ImageProcessorException("can't open the file");
        }
        unsigned char file_header[file_header_size];
        file.read(reinterpret_cast<char *>(file_header), file_header_size);
        unsigned char info_header[info_header_size];
        file.read(reinterpret_cast<char *>(info_header), info_header_size);

        if (file_header[0] != 'B' || file_header[1] != 'M') {
            file.close();
            throw ImageProcessorException("this is not a bitmap image");
        }

        size_t file_size = file_header[2] + (file_header[3] << 8) + (file_header[4] << 16) + (file_header[5] << 24);
        width_ = info_header[4] + (info_header[5] << 8) + (info_header[6] << 16) + (info_header[7] << 24);
        height_ = info_header[8] + (info_header[9] << 8) + (info_header[10] << 16) + (info_header[11] << 24);
        colors_ = std::vector<std::vector<Color>>(height_, std::vector<Color>(width_));
        const size_t padding_num = ((4 - (width_ * 3) % 4) % 4);

        for (size_t y = 0; y < height_; ++y) {
            for (size_t x = 0; x < width_; ++x) {
                unsigned char color[3];
                file.read(reinterpret_cast<char *>(color), 3);
                colors_[y][x].r = static_cast<double>(color[2]) / 255.0;
                colors_[y][x].g = static_cast<double>(color[1]) / 255.0;
                colors_[y][x].b = static_cast<double>(color[0]) / 255.0;
            }
            file.ignore(padding_num);
        }
        file.close();
    } catch (const ImageProcessorException& e){
        file.close();
        throw ImageProcessorException(e);
    } catch (const std::exception& e) {
        file.close();
        throw ImageProcessorException("file read error");
    }
}

size_t Image::GetWidth() const {
    return width_;
}

size_t Image::GetHeight() const {
    return height_;
}

void Image::Resize(size_t new_width, size_t new_height) {
    width_ = std::min(width_, new_width);
    height_ = std::min(height_, new_height);
    colors_ = std::vector<std::vector<Color>>(colors_.end() - height_, colors_.end());
    for (size_t i = 0; i < height_; ++i) {
        colors_[i].resize(width_);
    }
}


