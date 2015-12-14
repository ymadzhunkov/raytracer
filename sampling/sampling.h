// =====================================================================================
//
//       Filename:  sampling.h
//
//    Description:  
//
//        Version:  1.0
//        Created:  31.10.2015 17,10,40
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#include "vector.h"

// Random direction distributed uniformly on the surface of 3D sphere
struct UniformSphere {
   UnitVector dir;
};
// Random direction distributed uniformly on the surface of 3D helisphere,
// z >= 0
struct UniformHemiSphere {
   UnitVector dir;
};

struct UniformCircle {
   float x, y;
};

struct GaussRandom {
   float g;
};

// This class knows how to sample, but it has no idea what random generator is.
// This will enforce all sampling to be thread safe and deterministic.
class Sampler {
public:
   UniformSphere     getUniformSphere    (const UniformRandom r1, const UniformRandom r2) const;
   UniformHemiSphere getUniformHemiSphere(const UniformRandom r1, const UniformRandom r2) const;
   UniformCircle     getUniformCircle    (const UniformRandom r1) const;
   GaussRandom       getGaussRandom      (const UniformRandom r1) const;

};
