// =====================================================================================
//
//       Filename:  ranmar.h
//
//    Description:  
//
//        Version:  1.0
//        Created:   2.11.2015  9,09,30
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#pragma once

// Plain structure to hold a uniform random sample
struct UniformRandom {
public:
  float getValue() const { return r; }

private:
  friend class Ranmar;
  UniformRandom(const float r) : r(r) {}
  float r;
};

// implements Zaman & Marsaglia ranmar generator
// does not have virtual table
class Ranmar {
public:
	Ranmar(const unsigned int someSeed = 1802) {
		setSeed(someSeed);
	}
   // returns random number from in [0.0,1.0)
	UniformRandom getUniform(); 
	size_t stateSize() const { return sizeof(*this);};
	void setSeed(const unsigned int N) { setState(N, 9373);};
private:
	void setState(int ixx, int jxx);
   int        iseed1, iseed2;
   int        ix, jx, c;
   int        u[97];
   static     int cd, cm;
   static     float  twom24;
};
float Ranmar::twom24 = 1./16777216.;
int Ranmar::cd = 7654321;
int Ranmar::cm = 16777213;
void Ranmar::setState(int ixx, int jxx) {
  if (ixx <= 0 || ixx >= 31328)
    ixx = 1802;
  if (jxx <= 0 || jxx >= 30081)
    jxx = 9373;
  iseed1 = ixx;
  iseed2 = jxx;
  int i = (ixx / 177) % 177 + 2;
  int j = ixx % 177 + 2;
  int k = (jxx / 169) % 178 + 1;
  int l = jxx % 169;
  for (int ii = 0; ii < 97; ii++) {
    int s = 0;
    int t = 8388608;
    for (int jj = 0; jj < 24; jj++) {
      int m = (((i * j) % 179) * k) % 179;
      i = j;
      j = k;
      k = m;
      l = (53 * l + 1) % 169;
      if ((l * m) % 64 >= 32)
        s += t;
      t /= 2;
    }
    u[ii] = s;
  }
  c = 362436;
  ix = 96;
  jx = 32;
}
UniformRandom Ranmar::getUniform() {
  register int r = u[ix] - u[jx--];
  if (r < 0)
    r += 16777216;
  u[ix--] = r;
  if (ix < 0)
    ix = 96;
  if (jx < 0)
    jx = 96;
  c -= cd;
  if (c < 0)
    c += cm;
  r -= c;
  if (r < 0)
    r += 16777216;
  UniformRandom res(twom24 * r);
  return res;
}
