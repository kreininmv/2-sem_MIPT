#include <math.h>
#include <time.h>

namespace mk5
{
  class complex
  {
    double re, im;

  public:
    complex( double real, double image) : re(real), im(image){}

    complex operator+( const complex &C) {
      return complex(C.re + re, C.im + im);
    }

    complex & operator+=( const complex &C1 ) {
      re += C1.re;
      im += C1.im;
      return *this;
    }

    complex & operator-( void ) {
      re = -re;
      im = -im;
      return *this;
    }

    complex & operator-=( const complex &C1 ) {
      re -= C1.re;
      im -= C1.im;
      return *this;
    }

    complex  operator*( const complex &C1 ) { 
      return complex(re * C1.re - im * C1.im, re * C1.im + im * C1.re);
    }

    complex & operator*=( const complex &C) {
      double re1(re * C.re - im * C.im),
        im1(re * C.im + im * C.re);
      re = re1, im = im1;
      return *this;
    }

    double SqNorm(void) {
      return re * re + im * im;
    }

    double Norm(void) {
      return sqrt(re * re + im * im);
    }

    double Im(void) {
      return im;
    }

    double Re(void) {
      return re;
    }

    int Julia(double Re, double Im) {
      complex Z(re, im);
      complex Z0(Re, Im);
      int n = 0;
      while (n < 255 && (Z.re * Z.re + Z.im * Z.im) < 4)
      {
        Z = Z * Z  + Z0;
        n++;
      }

      return n;
    }

    int MandelBrot(void) {
      complex Z(re, im);
      //complex Z(re, im), Z0(cos(clock() / (double)CLOCKS_PER_SEC), cos(clock() / (double)CLOCKS_PER_SEC));
      int n = 0;
      
      while (n < 255 && Z.SqNorm() < 4) {
        Z = Z * Z + *this;
        n++;
      }
      
      return n;
    }
  };
}