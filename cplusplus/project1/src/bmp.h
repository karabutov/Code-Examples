#pragma once
#include <iostream>
#include <fstream>
#include <vector>

class BmpInfo;
class Color;

Color average(const std::vector<Color>& v);

double dist(const Color& a, const Color& b);

class BmpHeader {
    unsigned short bfType = 0x4d42;
    unsigned int bfSize;
    unsigned short bfRes1 = 0;
    unsigned short bfRes2 = 0;
    unsigned int bfOffBits = 0x36;
public:
    void write(std::ostream& out);
    BmpHeader(unsigned int size);
    ~BmpHeader() {}
};

class BmpInfo {
    unsigned int biSize;/* Size of info header */
    int biWidth;/* Width of image */
    int biHeight;/* Height of image */
    unsigned short biPlanes = 1;/* Number of color planes */
    unsigned short biBitCount = 24;/* Number of bits per pixel */
    unsigned int biCompression = 0;/* Type of compression to use */
    unsigned int biSizeImage = 0;/* Size of image data */
    int biXPelsPerMeter = 5000;/* X pixels per meter */
    int biYPelsPerMeter = 5000;/* Y pixels per meter */
    unsigned int biClrUsed = 0;/* Number of colors used */
    unsigned int biClrImportant = 0;/* Number of important colors */
    public:
    void write(std::ostream& out);
    BmpInfo(int w, int h): biWidth(w), biHeight(h), biSize(sizeof(BmpInfo)) {}
    ~BmpInfo() {}
};

class Color {
public:
    unsigned char r, g, b;
    Color(unsigned char R, unsigned char G, unsigned char B): r(R), g(G), b(B) {}
    ~Color() {}
    void write(std::ostream& out);
    void set_intensity(double t);
    friend Color average(const std::vector<Color>& v);
    friend double dist(const Color& a, const Color& b);
};
