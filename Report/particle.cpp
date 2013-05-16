#include "particle.hpp"

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

Particle::Particle(): position(0,0,0), velocity(0,0,0), color(1,0,0),
lifetime(1e6), age(0), size(0.2), transparency(0), shape(Sphere){

}

Particle::~Particle(){
}

void Particle::draw(){
	glPushMatrix();
	glTranslatef(position[0], position[1], position[2]);
	if(shape == Sphere)
		glutSolidSphere(size, 10,10);
	else if(shape == Cubic)
		glutSolidCube(size);
	glPopMatrix();
}

void Particle::collision(Particle &other){
	Vector3f distance = position - other.position;
	float dist = distance.squaredNorm();
	if(dist < sqr(size+other.size)){
		Vector3f displace = distance.dot(-velocity + other.velocity)*distance/dist;
		velocity += displace;
		other.velocity -= displace;
	}
}
