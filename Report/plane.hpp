/*
 * plane.h
 *
 *  Created on: May 16, 2013
 *      Author: letrungkien7
 */

#ifndef PLANE_HPP_
#define PLANE_HPP_

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

using namespace std;
using namespace Eigen;

class Plane {
public:
	Vector3f normal;
	vector<Vector3f> points;
	Plane();
	virtual ~Plane();
};

#endif /* PLANE_H_ */
