#ifndef __GrayScott_h__
#define __GrayScott_h__

class GrayScott
{
 public:
  GrayScott(void);
  GrayScott(int width, int height,
	    double f, double k, double Ru, double Rv, int putRadius);
  virtual ~GrayScott(void);

  void update(void);
  void put(const int& x, const int& y);

  double** u;
  double** v;
  double** pu;
  double** pv;

 private:
  const int _width;
  const int _height;
  const double _f;
  const double _k;
  const double _Ru;
  const double _Rv;
  const int _radius;

  void _createUV(void);
};

#endif /* __Gray_Scott_h__ */
