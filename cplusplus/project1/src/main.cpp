#include "render.h"
#include <sstream>

void scene1(double* spec, double* dir, char* file) {
    double v[3] = {1, 0.05, 1};
    Object* ob1 = new Sphere(v, 1, Color(255, 50, 100), 0.9);

    double v9[3] = {1, 0.05, 4};
    Object* ob7 = new Sphere(v9, 1.5, Color(255, 50, 100), 0);

	double vec21[3] = {1,0,0}, vec22[3] = {0,0,1}, O2[3] = {0, -1, 0};
    Object* ob2 = new Plane(O2, vec21, vec22, Color(0, 255, 0), 25, 4, 10, 0);

	double vec1[3] = {1, 0, 0}, vec2[3] = {0, 1, 0}, O[3] = {0, 0, -1.5};
	Object* ob4 = new Plane(O, vec1, vec2, Color(100, 100, 100), 10, 21, 1024, 0); 

	double e[3] = {0, 1, 0}, B[3] = {1, -1, -0.5};
	Object* ob3 = new Cylinder(B, e, 0.25, 1.3, Color(10, 50, 255), 25, 2, 10, 0);

	double e1[3] = {0, 0, 1}, B1[3] = {1, 2, 0.5};
	Object* ob6 = new Cylinder(B1, e1, 0.25, 2.3, Color(10, 150, 155), 5, 20, 512, 0);

	double vec31[3] = {0, 0, 1}, vec32[3] = {0, 1, 0}, O3[3] = {3, 0, 0};
	Object* ob5 = new Plane(O3, vec31, vec32, Color(255, 140, 0), 25, 20, 8, 0); 

    std::vector<Object*> obj;
    obj.push_back(ob1);
	obj.push_back(ob2);
    obj.push_back(ob3);
	obj.push_back(ob4);
	obj.push_back(ob5);
	obj.push_back(ob6);
	obj.push_back(ob7);


	double lo[3] = {1, 4, 0};
	Light l(lo, 1);
	double lo1[3] = {-4, 0.5, 0};
	Light l1(lo, 1);
	std::vector<Light> L;
	L.push_back(l);
	L.push_back(l1);
    Image im(2, 2, 800, 800, obj, L, spec, dir, Color(0, 0, 0), 8);
    im.process();
    std::stringstream ss;
    ss << file;
    std::ofstream out(ss.str(), std::ios_base::out | std::ios_base::binary);
    im.write(out);
    out.close();
    std::cout << ss.str() << " generated\n" << std::flush;
    delete ob1;
	delete ob2;
	delete ob3;
	delete ob4;
	delete ob5;
	delete ob6;
	delete ob7;
}

int main(int argc, char **argv) {
    std::stringstream ss1(argv[1]);
    std::stringstream ss2(argv[2]);
    double spec[3], dir[3];
    ss1 >> spec[0] >> spec[1] >> spec[2];
    ss2 >> dir[0] >> dir[1] >> dir[2];
    scene1(spec, dir, argv[3]);
    return 0;
}
