#pragma once
#include "geometry.h"
#include <vector>
#include <omp.h>

class Image {
    double xsize, ysize;
    int height, width;
    std::vector<Color> arr;
    std::vector<Object*> obj;
    double spec[3], direction[3];
    Color background;
	std::vector<Light> L;
	int antialiasing;
public:
    void process();
    Image(double x, double y, int h, int w, const std::vector<Object*> &o, const std::vector<Light> l, const double* s, const double* dir, Color BG, int aa);
           
    virtual ~Image() {}
    void write(std::ostream& out);
};
