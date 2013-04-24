#include <stdio.h>
#include "GrayScott.h"

GrayScott::GrayScott(void)
 :_width(128), _height(128), _f(0.02), _k(0.04), _Ru(0.01), _Rv(0.005), _radius(0)
{
  _createUV();
}

GrayScott::GrayScott(int width, int height,
		     double f, double k, double Ru, double Rv, int putRadius)
  :_width(width), _height(height),
   _f(f), _k(k), _Ru(Ru), _Rv(Rv), _radius(putRadius*putRadius)
{
  _createUV();
}

GrayScott::~GrayScott(void)
{
  if (u != 0)
    {
      for (int i = 0; i < _width + 2; i++)
	{
	  if (u[i] != 0)
	    delete [] u[i];
	}
      delete [] u;
    }

  if (pu != 0)
    {
      for (int i = 0; i < _width + 2; i++)
	{
	  if (pu[i] != 0)
	    delete [] pu[i];
	}
      delete [] pu;
    }

  if (v != 0)
    {
      for (int i = 0; i < _width + 2; i++)
	{
	  if (v[i] != 0)
	    delete [] v[i];
	}
      delete [] v;
    }

  if (pv != 0)
    {
      for (int i = 0; i < _width + 2; i++)
	{
	  if (pv[i] != 0)
	    delete [] pv[i];
	}
      delete [] pv;
    }
}

void GrayScott::_createUV(void)
{
  u = new double* [_width+2];
  v = new double* [_width+2];
  pu = new double* [_width+2];
  pv = new double* [_width+2];

  for (int i = 0; i < _width+2; i++)
    {
      u[i] = new double[_height+2];
      v[i] = new double[_height+2];
      pu[i] = new double[_height+2];
      pv[i] = new double[_height+2];

      for (int j = 0; j < _height+2; j++)
	{
	  u[i][j] = 1.0;
	  v[i][j] = 0.0;
	}
    }
}

void GrayScott::update(void)
{
  static int t = 0;
  t++;
  printf(" %d th step\n", t);

  for (int i = 0; i < _width+2; i++)
    {
      for (int j = 0; j < _height+2; j++)
	{
	  pu[i][j] = u[i][j];
	  pv[i][j] = v[i][j];
	}
    }

  for (int i = 1; i < _width+1; i++)
    {
      for (int j = 1; j < _height+1; j++)
	{
	  //重要！！
	  double tmp = pu[i][j] * pv[i][j] * pv[i][j];
	  u[i][j] = u[i][j] + _Ru * (pu[i+1][j] + pu[i-1][j] + pu[i][j+1] + pu[i][j-1] - 4 * pu[i][j])
	    - tmp + _f * (1.0 - pu[i][j]);
	  v[i][j] = v[i][j] + _Rv * (pv[i+1][j] + pv[i-1][j] + pv[i][j+1] + pv[i][j-1] - 4 * pv[i][j])
	    + tmp - (_f + _k) * pv[i][j];
	}
    }

  for (int i = 1; i < _width + 1; i++)
    {
      u[i][0] = u[i][_height];
      u[i][_height+1] = u[i][1];
      v[i][0] = v[i][_height];
      v[i][_height+1] = v[i][1];
    }

  for (int j = 1; j < _height + 1; j++)
    {
      u[0][j] = u[_width][j];
      u[_width+1][j] = u[1][j];
      v[0][j] = v[_width][j];
      v[_width+1][j] = v[1][j];
    }
}

void GrayScott::put(const int& x, const int& y)
{
  static const int l = _radius + 1;
  static const int r2 = _radius * _radius;

  int is = (x - l > 0) ? x - l : 0;
  int ie = (x + l < _width + 2) ? x + l : _width + 2;
  int js = (y - l > 0) ? y - l : 0;
  int je = (y + l < _height + 2) ? y + l : _height + 2;

  for (int i = is; i < ie; i++)
    {
      for (int j = js; j < je; j++)
	{
	  if ((i - x) * (i - x) + (j - y) * (j - y) < r2)
	    {
	      u[i][j] = 0.25;
	      v[i][j] = 0.33 * 2;
	    }
	}
    }
}
