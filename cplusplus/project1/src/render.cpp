#include "render.h"

double my_rand() {
    return (double) rand() / RAND_MAX;
}

Image::Image(double x, double y, int h, int w, const std::vector<Object*> &o, const std::vector<Light> l, const double* s, const double* dir, Color BG, int aa):
               xsize(x), ysize(y), height(h), width(w), obj(o), background(BG), L(l), antialiasing(aa)
{
    arr.reserve(height * width);
    for(int i = 0; i < 3; i++) {
        spec[i] = s[i];
        direction[i] = dir[i];
    }
	norm(direction, 3);
}

void Image::process() {
    double v[3];
    double up[3] = {0, 1, 0}, right[3];
    double dp = dotProduct(up, direction, 3);
    for(int i = 0; i < 3; i++) {  //
        up[i] -= dp * direction[i];
    }
	norm(up, 3);
    vectProd(direction, up, right);
	arr = std::vector<Color>(height * width, Color(0,0,0));
	#pragma omp parallel for collapse(2) private(v)
    for(int i = 0; i < height; i++) {
        for(int j = 0; j < width; j++) {
            Color c(0, 0, 0);
            double x = double(j);
            double y = double(i);
            v[0] = xsize * (x / width - 0.5) * right[0] + ysize * (y / height - 0.5) * up[0] + direction[0];
            v[1] = xsize * (x / width - 0.5) * right[1] + ysize * (y / height - 0.5) * up[1] + direction[1];
            v[2] = xsize * (x / width - 0.5) * right[2] + ysize * (y / height - 0.5) * up[2] + direction[2];
            Ray r(spec, v);
            int index = -1; 
			rayTrace(r, obj, index, nullptr);
            if(index < 0) {
                c = background;
            }
			else {
				c = obj[index]->get_color(r.cur_pos, L, obj, index, spec);
			}
			arr[i * width + j] = c;
        }
    }
	if(antialiasing == 1) return;

	//antialiasing
	std::vector<Color> vect;
	std::vector<Color> copy = arr;
	#pragma omp parallel for collapse(2) private(vect, v)
    for(int i = 2; i < height - 2; i++) {
        for(int j = 2; j < width - 2; j++) {
            double d = 0;
            for(int I = -2; I < 3; I++) {
                for(int J = -2; J < 3; J++) {
                    double c = dist(copy[i * width + j], copy[(i + I) * width + (j + J)]);
                    if(c > d) d = c;
                }
            }
            if(d > 120) {
                Color c(0, 0, 0);
                vect.clear();
                vect.reserve(antialiasing + 1);
                vect.push_back(copy[i * width + j]);
                for(int z = 0; z < antialiasing; z++) {
                    for(int q = 0; q < antialiasing; q++) {
                        double randomx = double(j) + (my_rand() + (double)z) / antialiasing;
                        double randomy = double(i) + (my_rand() + (double)q) / antialiasing;
                        v[0] = xsize * (randomx / width - 0.5) * right[0] + ysize * (randomy / height - 0.5) * up[0] + direction[0];
                        v[1] = xsize * (randomx / width - 0.5) * right[1] + ysize * (randomy / height - 0.5) * up[1] + direction[1];
                        v[2] = xsize * (randomx / width - 0.5) * right[2] + ysize * (randomy / height - 0.5) * up[2] + direction[2];
                        Ray r(spec, v);
                        int index = -1; 
						rayTrace(r, obj, index, nullptr);
                        if(index < 0) {
                            c = background;
                        }
						else {
							c = obj[index]->get_color(r.cur_pos, L, obj, index, spec);
						}
						vect.push_back(c);
                    }
                }
                arr[i * width + j] = average(vect);
            }
        }
    }
}

void Image::write(std::ostream& out) {
    BmpHeader h(height * width);
    BmpInfo I(width, height);
    h.write(out);
    I.write(out);
    for(auto& i : arr) {
        i.write(out);
    }
}