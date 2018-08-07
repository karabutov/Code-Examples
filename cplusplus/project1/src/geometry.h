#include <cmath>
#include "bmp.h"
#include <vector>

double dotProduct(const double* v1, const double* v2, int n);

void reflect(const double* x, const double* n, double* ref);

void vectProd(const double* x, const double* y, double* res);

void norm(double *vec, unsigned int n);

class Light;

class Ray {
public:
	double begin[3]; 
	double direction[3];
	double cur_pos[3];
	Ray(const Ray& other);
	Ray(const double *b, const double *d);
	~Ray() {}
	void make_step(double step);
	double path();
};

class Object {
public:
	virtual void get_normal(const double *point, double *n)=0;
	virtual double distance(const double *point)=0;
	virtual Color get_color(const double *point, const std::vector<Light>& L, std::vector<Object*> &obj, int index, const double* spec)=0;
	virtual ~Object() {}
};

class Sphere: public Object {
	double centr[3], r;	
public:
	double refl;
	Color c;
	Sphere(const double *O, const double R, const Color &C, double ref);
	~Sphere() {}
	virtual void get_normal(const double *point, double *n);
	virtual double distance(const double *point);
	virtual Color get_color(const double *point, const std::vector<Light>& L, std::vector<Object*> &obj, int index, const double* spec);
	double norma(const double *point);
};

class Plane: public Object{
	double O[3];
	double vec1[3], vec2[3];
	double n[3];
	Color c;
	double diffuse , p, specular;
public:	
	double refl;
	virtual void get_normal(const double *point, double *nor){
		for(int i = 0; i < 3; i++){
			nor[i] = n[i];
		}	
	}
	virtual double distance(const double *point);
	Plane(const double *p, const double *v1, const double *v2, const Color &col, double dif, double pp, double spec, double ref);
	virtual Color get_color(const double *point, const std::vector<Light>& L, std::vector<Object*> &obj, int index, const double* spec);

};

class Cylinder: public Object{
	double O[3], vec[3];
	double r, height;
	Color c;
	double diffuse , p, specular;
public:
	virtual void get_normal(const double *point, double *n){};
	double refl;
	virtual double distance(const double *point);
	Cylinder(const double *poi, const double *v, double rad, double h, const Color &col, double dif, double pp, double spec, double ref);
	virtual Color get_color(const double *point, const std::vector<Light>& L, std::vector<Object*> &obj, int index, const double* spec);
	double infinitydist(const double *point, double& scalar);
};

class Light{
public:
	double location[3];
	double intens;
	Light(const double *point, const double i);
	bool is_shadow(const double *point, std::vector<Object*> &obj, int index) const;
};

double min_distance(std::vector<Object*> &obj, int &index, const Object* ex);

void rayTrace(Ray &r, std::vector<Object*> &obj, int &index, const Object* ex);

double norma(const double *vec, unsigned int n);