#pragma once

#include <cstdint>
#include <vector>
#include "exceptions.h"

struct Color {
    double r, g, b;
    Color();
    Color(double r, double g, double b);
    ~Color();
    Color operator+(const Color & other) const;
    Color operator-(const Color & other) const;
    Color& operator=(const Color & other);
    Color& operator+=(const Color & other);
    Color operator*(double other) const;
    Color operator/(double other) const;
    void Clamp();
};

class Image {
public:
    Image(size_t width, size_t height);
    explicit Image(const char* path);
    Image(const Image&);
    ~Image();

    void SetColor(const Color&, size_t x, size_t y);
    Color GetColor(ssize_t x, ssize_t y) const;
    void Export(const char* path);
    void Read(const char* path);
    size_t GetWidth() const;
    size_t GetHeight() const;
    void Resize(size_t new_width, size_t new_height);
private:
    size_t width_;
    size_t height_;
    std::vector<std::vector<Color>> colors_;
};
