#ifndef PARTICLE_HPP
#define PARTICLE_HPP

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


	Particle(): position(0,0,0), velocity(0,0,0), color(1,0,0),
			lifetime(1e6), age(0), size(1), transparency(0), shape(Sphere){

	}

	~Particle(){
	}

	void draw(){
		if(shape == Sphere)
			glutSolidSphere(size, 10,10);
		else if(shape == Cubic)
			glutSolidCube(size);
	}

	void collision(Particle &other){
		Vector3f distance = position - other.position;
		float dist = distance.squaredNorm();
		if(dist < sqr(size+other.size)){
			Vector3f displace = ((-velocity + other.velocity)*distance)*distance/dist;
			velocity += displace;
			other.velocity -= displace;
		}
	}
};


#endif
