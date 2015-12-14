// =====================================================================================
//
//       Filename:  main.cpp
//
//    Description:  
//
//        Version:  1.0
//        Created:  31.10.2015 11,29,41
//       Revision:  none
//       Compiler:  g++
//
//         Author:  Yordan Madzhunkov (), ymadzhunkov@gmail.com
//   Organization:  
//
// =====================================================================================
#include "platform.h"
#include "config.h" // Version defined here
#include "intrinsics.h"
#include "atomic.h"
#include "ranmar.h"
#include "kernel.h"
#include "managers.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
  printf("raytracer version %d.%d\n", raytracer_VERSION_MAJOR,
         raytracer_VERSION_MINOR);

   Ranmar rnd(120);
   for (uint32 i = 0; i < 1; i++) {
      printf("%f\n", rnd.getUniform().getValue());
   }

  return 0;
}
