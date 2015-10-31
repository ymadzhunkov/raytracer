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
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(int argc, char *argv[]) {
  printf("raytracer version %d.%d\n", raytracer_VERSION_MAJOR,
         raytracer_VERSION_MINOR);
  if (argc < 2) {
    fprintf(stdout, "Usage: %s number\n", argv[0]);
    return 1;
  }
  double inputValue = atof(argv[1]);
  double outputValue = sqrt(inputValue);
  fprintf(stdout, "The square root of %g is %g\n", inputValue, outputValue);
  return 0;
}
