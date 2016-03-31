/*
 *  Intel MIC / KNC Power measurements 
 * 
 *  Copyright (C) 2016 by Fabio Baruffa <fbaru.dev@gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>. 
 *
 */


#include "micpower.hpp"

#include <iostream>       // std::cout, std::endl
#include <omp.h>

#define N 10000000
#define R 10000
double f(double a) { return (4.0 / (1.0 + a*a));} 

int main() 
{
  micpower pwr;
     
   pwr.start();
   std::cout << "Start countdown and power measure!\n";

  for (int i=5; i>0; --i) {

    std::cout << i << std::endl;
    sleep(1);
  }
  std::cout << "Stop countdown and power measure!\n";
  pwr.stop();
    
  std::cout << "Start countdown NO power measure!\n";
    for (int i=5; i>0; --i) {

    std::cout << i << std::endl;
    sleep(1);
  }
  std::cout << "Stop countdown NO power measure!\n";
 
  pwr.start();
  std::cout << "Start power measure and PI computation!\n";

  double fSum = 0.0;
  double fX;
  const double fH   = 1.0 / (double) N;
  double PI = 0.0;
  double fTimeStart, fTimeEnd;
  
  fTimeStart = omp_get_wtime();
//Compute the PI using the definition as integral
// \int_0^1 4/(1+x*x) dx
  for (int j = 0; j < R; ++j) {
#pragma omp parallel for private(fX) reduction(+:fSum)
    for (int i = 0; i < N; ++i) {
        fX = fH * ((double)i + 0.5);
        fSum += f(fX);
    }
    PI += fH * fSum;
    fSum = 0.0;
  }
  fTimeEnd = omp_get_wtime();
  
  std::cout << "Stop power measure and PI computation!\n";
  std::cout << "Time = " << fTimeEnd - fTimeStart << " sec.\n";
  std::cout << "PI = " << PI/R << std::endl;

  pwr.stop();
  
  return 0;
}
