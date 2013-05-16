#ifndef PARTICLE_HPP_
#define PARTICLE_HPP_

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cstdio>
#include <string>
#include <cmath>

#include <GL/glut.h>
#include <eigen3/Eigen/Dense>
#include <opencv2/opencv.hpp>

#define sqr(x) x*x

using namespace std;
using namespace Eigen;

enum Shape {Sphere, Cubic};

class Particle{
public:
	Vector3f position;
	Vector3f velocity;
	Vector3f color;
	float lifetime;
	float age;
	float size;
	float transparency;
	Shape shape;

	Particle();
	virtual ~Particle();
	void draw();
	void collision(Particle &other);
};

#endif
