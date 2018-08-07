#include "geometry.h"

void vectProd(const double* x, const double* y, double* res) {
    res[0] = x[1]*y[2] - x[2]*y[1];
    res[1] = x[2]*y[0] - x[0]*y[2];
    res[2] = x[0]*y[1] - x[1]*y[0];
}

void reflect(const double* x, const double* n, double* ref) {
    double w = dotProduct(x, n, 3), tmp[3];
    for(int i = 0; i < 3; i++) {
        tmp[i] = (-x[i] + 2 * n[i] * w);
    }
	for(int i = 0; i < 3; i++) {
        ref[i] = tmp[i];
    }
}

void another_reflect(const double* x, const double* n, double* ref) {
    double w = dotProduct(x, n, 3);
    if(w > 0) w = -w;
    for(int i = 0; i < 3; i++) {
        ref[i] = (x[i] - 2 * n[i] * w);
    }
}

double dotProduct(const double* v1, const double* v2, int n) {
    double res = 0;
    for(int i = 0; i < n; i++) {
        res += v1[i] * v2[i];
    }
    return res;
}

double norma(const double *vec, unsigned int n){
	double sum = dotProduct(vec, vec, n);
	sum = sqrt(sum);
	return sum;
}


void norm(double *vec, unsigned int n){
	double sum = dotProduct(vec, vec, n);
	sum = sqrt(sum);
	for(unsigned int i = 0; i < n; i++){
		vec[i] = vec[i]/sum;
	}
}

double min_distance(const std::vector<Object*> &obj, const double *point, int &index, const Object* ex){
	double min_dist = 100000.0;
	for(unsigned int i = 0; i < obj.size(); i++){
		if(obj[i] == ex) continue;
		double dist = obj[i]->distance(point);
		if(dist < min_dist){
			index = i;
			min_dist = dist;	
		}
	}
	return min_dist;
}

void rayTrace(Ray &r, std::vector<Object*> &obj, int &index, const Object* ex){
	double step = 0.0;
	double dist = 1.0;
	double path = 0;
	index = -1;
	while(dist > 0.0001){
		r.make_step(step);
		dist = min_distance(obj, r.cur_pos, index, ex);
		path += dist;
		if(path > 100.0){
			index = -1;
			return;		
		}
		step = dist;
	}
	return;
}

Ray::Ray(const double* b, const double* d) {
    for(int i = 0; i < 3; i++) {
        begin[i] = b[i];
        direction[i] = d[i];
		cur_pos[i] = begin[i];
    }
	norm(direction, 3);
}

Ray::Ray(const Ray& other) {
    for(int i = 0; i < 3; i++) {
        begin[i] = other.begin[i];
        direction[i] = other.direction[i];
		cur_pos[i] = begin[i];
    }
	norm(direction, 3);
}

double Ray::path() {
	double v[3];
	for(int i = 0; i < 3; i++) {
		v[i] = cur_pos[i] - begin[i];
	}
	return sqrt(dotProduct(v, v, 3));
}

void Ray::make_step(double step){

	double dx = direction[0] * step;
	double dy = direction[1] * step;
	double dz = direction[2] * step;
	
	cur_pos[0] += dx;
	cur_pos[1] += dy;
	cur_pos[2] += dz;
}

Sphere::Sphere(const double *O, const double R, const Color &C, double ref): c(C), refl(ref){
	centr[0] = O[0];
	centr[1] = O[1];
	centr[2] = O[2];
	r = R;
}

double Sphere::norma(const double *point){
	double n = 0;	
	for(unsigned int i = 0; i < 3; i++){
		n += (point[i] - centr[i])*(point[i] - centr[i]);
	}
	n = sqrt(n);
	return n;
}

double Sphere::distance(const double *point){
    return std::max(Sphere::norma(point) - r, 0.0);
}

void Sphere::get_normal(const double *point, double *n){
	for(int i = 0; i < 3; i++) {
		n[i] = point[i] - centr[i];
	}
	norm(n, 3);
}

Color Sphere::get_color(const double *point, const std::vector<Light>& L, std::vector<Object*> &obj, int index, const double* spec){
	double vect_to_light[3], n[3], vect_to_spec[3], reflection[3];
	get_normal(point, n);
	Color tmp = c;
	double intens = 0.3, diffuse = 10, l, p = 500, specular = 50;
	for(auto& i : L) {
		if(!(i.is_shadow(point, obj, index))) {
			for(int j = 0; j < 3; j++) {
				vect_to_light[j] = i.location[j] - point[j];
			}	
			l = dotProduct(vect_to_light, vect_to_light, 3);
			norm(vect_to_light, 3);
			intens += diffuse * dotProduct(n, vect_to_light, 3) / l; //diffuse
			for(int j = 0; j < 3; j++) {
				vect_to_spec[j] = spec[j] - point[j];
			}
			norm(vect_to_spec,3);
			reflect(vect_to_light, n, reflection);
			intens += specular * pow(std::max(dotProduct(vect_to_spec, reflection, 3), 0.0), p) / l; //specular
		}
	}
	tmp.set_intensity(intens);
	if(refl > 0.0){
		Color refl_color(0,0,0);
		int ind = -1;
		double vec[3], new_dir[3];
		this->get_normal(point, vec);
		for(int j = 0; j < 3; j++) {
			vect_to_spec[j] = -spec[j] + point[j];
		}
		another_reflect(vect_to_spec, vec, new_dir);
		Ray r1(point, new_dir);
		rayTrace(r1, obj, ind, this);
		if(ind >= 0){
			refl_color = obj[ind]->get_color(r1.cur_pos, L, obj, ind, point);			
		}
		tmp.r = std::min((int)((int)(tmp.r)*(1 - refl) + (int)(refl_color.r)*refl), 255);
		tmp.g = std::min((int)((int)(tmp.g)*(1 - refl) + (int)(refl_color.g)*refl), 255);
		tmp.b = std::min((int)((int)(tmp.b)*(1 - refl) + (int)(refl_color.b)*refl), 255);
	}
	return tmp;
}

double Plane::distance(const double *point){
	double res[3];
	res[0] = point[0] - O[0];
	res[1] = point[1] - O[1];
	res[2] = point[2] - O[2];
	return fabs(dotProduct(res, n, 3));
}

Plane::Plane(const double *poi, const double *v1, const double *v2, const Color &col, double dif, double pp, double spec, double ref): c(col)
{
	refl = ref;
	diffuse = dif;
	p = pp;
	specular = spec;
	for(int i = 0; i < 3; i++){
		O[i] = poi[i];
		vec1[i] = v1[i];
		vec2[i] = v2[i];
	}
	vectProd(vec1, vec2, n);
	norm(n, 3);
}

Color Plane::get_color(const double *point, const std::vector<Light>& L, std::vector<Object*> &obj, int index, const double* spec){
	double vect_to_light[3], vect_to_spec[3], refl[3];
	Color tmp = c;
	double intens = 0.3, l;//, diffuse = 25, p = 4, specular = 10;
	for(auto& i : L) {
		if(!i.is_shadow(point, obj, index)) {
			for(int j = 0; j < 3; j++) {
				vect_to_light[j] = i.location[j] - point[j];
			}
			l = dotProduct(vect_to_light, vect_to_light, 3);
			norm(vect_to_light, 3);
			intens += this->diffuse * fabs(dotProduct(n, vect_to_light, 3)) / l; //diffuse
			for(int j = 0; j < 3; j++) {
				vect_to_spec[j] = spec[j] - point[j];
			}
			norm(vect_to_spec,3);
			reflect(vect_to_light, n, refl);
			intens += this->specular * pow(std::max(dotProduct(vect_to_spec, refl, 3), 0.0), this->p) / l; //specular
		}	
	}
	tmp.set_intensity(intens);
	return tmp;
}

double Cylinder::distance(const double *point){
	double scalar = 0;
	double d = std::max(infinitydist(point, scalar), 0.0), c = 0;
	if(scalar > height) {
		c = scalar - height;
	}
	else if(scalar < 0) {
		c = -scalar;
	}
	return sqrt(d*d + c*c);
		
}

double Cylinder::infinitydist(const double *point, double& scalar){
	double res[3];
	res[0] = point[0] - O[0];
	res[1] = point[1] - O[1];
	res[2] = point[2] - O[2];
	scalar = dotProduct(res, vec, 3);
	res[0] = point[0] - (scalar*vec[0] + O[0]);
	res[1] = point[1] - (scalar*vec[1] + O[1]);
	res[2] = point[2] - (scalar*vec[2] + O[2]);
	return norma(res, 3) - r;
}

Cylinder::Cylinder(const double *poi, const double *v, double rad, double h, const Color &col, double dif, double pp, double spec, double ref): c(col)
{	
	refl = ref;
	r = rad;
	height = h;	
	diffuse = dif;
	p = pp;
	specular = spec;
	for(int i = 0; i < 3; i++){
		O[i] = poi[i];
		vec[i] = v[i];
	}
	norm(vec, 3);
}

Color Cylinder::get_color(const double *point, const std::vector<Light>& L, std::vector<Object*> &obj, int index, const double* spec){
	double vect_to_light[3], n[3], vect_to_spec[3], refl[3];
	double fict;
	double x = infinitydist(point, fict);
	if(fict >= 0.01 && fict <= height - 0.01) {
		double res[3];
		n[0] = point[0] - O[0];
		n[1] = point[1] - O[1];
		n[2] = point[2] - O[2];
		n[0] -= fict*vec[0];
		n[1] -= fict*vec[1];
		n[2] -= fict*vec[2];
		norm(n, 3);
	}
	else {
		if(fict < 0.01) {
			n[0] = -vec[0];
			n[1] = -vec[1];
			n[2] = -vec[2];
		}
		else {
			n[0] = vec[0];
			n[1] = vec[1];
			n[2] = vec[2];
		}
	}	
	Color tmp = c;
	double intens = 0.3, l;//, diffuse = 25, l, p = 2, specular = 10;
	for(auto& i : L) {
		if(!i.is_shadow(point, obj, index)) {
			for(int j = 0; j < 3; j++) {
				vect_to_light[j] = i.location[j] - point[j];
			}
			l = dotProduct(vect_to_light, vect_to_light, 3);
			norm(vect_to_light, 3);
			intens += diffuse * dotProduct(n, vect_to_light, 3) / l; //diffuse
			for(int j = 0; j < 3; j++) {
				vect_to_spec[j] = spec[j] - point[j];
			}
			norm(vect_to_spec,3);
			reflect(vect_to_light, n, refl);
			intens += specular * pow(std::max(dotProduct(vect_to_spec, refl, 3), 0.0), p) / l; //specular
			
		}	
	}
	tmp.set_intensity(intens);
	return tmp;
}

Light::Light(const double *point, const double i){
	for(unsigned int i = 0; i < 3; i++){
		location[i] = point[i];
	}
	intens = i;
}

bool Light::is_shadow(const double *point, std::vector<Object*> &obj, int index) const {
	bool indicator = true;
	int local_index;
	double dir[3] = {point[0] - location[0], point[1] - location[1], point[2] - location[2]};
	Ray r(location, dir);
	rayTrace(r, obj, local_index, nullptr);
	if(local_index == -1){			
		return false;
	}
	if (local_index == index){
		double error[3];
		for(int i = 0; i < 3; i++) {
			error[i] = r.cur_pos[i] - point[i];
		}
		if(dotProduct(error, error, 3) > 0.0001) return true;
		return false;	
	}
	
	return true;
}