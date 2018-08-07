#include <cmath>
#include <bitset>
#include "bmp.h"

//код частично взят со stackoveflow.com
//
void BmpHeader::write(std::ostream& out) {
    out.write(reinterpret_cast<const char*>(&bfType), sizeof bfType);//bfType; //std::bitset<16>(bfType);
    out.write(reinterpret_cast<const char*>(&bfSize), sizeof bfSize);
    out.write(reinterpret_cast<const char*>(&bfRes1), sizeof bfRes1);
    out.write(reinterpret_cast<const char*>(&bfRes2), sizeof bfRes2);
    out.write(reinterpret_cast<const char*>(&bfOffBits), sizeof bfOffBits);
}

BmpHeader::BmpHeader(unsigned int size): bfSize(size * 3 + sizeof(BmpHeader) + sizeof(BmpInfo) + 2) {}

void BmpInfo::write(std::ostream& out) {
    out.write(reinterpret_cast<const char*>(&biSize), sizeof biSize);
    out.write(reinterpret_cast<const char*>(&biWidth), sizeof biWidth);
    out.write(reinterpret_cast<const char*>(&biHeight), sizeof biHeight);
    out.write(reinterpret_cast<const char*>(&biPlanes), sizeof biPlanes);
    out.write(reinterpret_cast<const char*>(&biBitCount), sizeof biBitCount);
    out.write(reinterpret_cast<const char*>(&biCompression), sizeof biCompression);
    out.write(reinterpret_cast<const char*>(&biSizeImage), sizeof biSizeImage);
    out.write(reinterpret_cast<const char*>(&biXPelsPerMeter), sizeof biXPelsPerMeter);
    out.write(reinterpret_cast<const char*>(&biYPelsPerMeter), sizeof biYPelsPerMeter);
    out.write(reinterpret_cast<const char*>(&biClrUsed), sizeof biClrUsed);
    out.write(reinterpret_cast<const char*>(&biClrImportant), sizeof biClrImportant);
}

void Color::write(std::ostream& out) {
    out.write(reinterpret_cast<const char*>(&b), sizeof b);
    out.write(reinterpret_cast<const char*>(&g), sizeof g);
    out.write(reinterpret_cast<const char*>(&r), sizeof r);
}
//

void Color::set_intensity(double t) {
    t += 0.3; 
    unsigned int R = (double)r * t;
    unsigned int G = (double)g * t;
    unsigned int B = (double)b * t;
    if(R > 255) r = 255;
    else r = R;
    if(G > 255) g = 255;
    else g = G;
    if(B > 255) b = 255;
    else b = B;
}


Color average(const std::vector<Color>& v) {
    unsigned int r = 0, g = 0, b = 0;
    for(auto &i : v) {
        r += i.r;
        g += i.g;
        b += i.b;
    }
    return Color(r/v.size(), g/v.size(), b/v.size());
}

double dist(const Color& a, const Color& b) {
    return fabs((double)a.r - b.r) + fabs((double)a.g - b.g) + fabs((double)a.b - b.b);
}
