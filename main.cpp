#include <iostream>
#include <time.h>

#include "lstm.h"
#include "matrix.h"
#include "vector.h"


void init( lstm::lstm_cell& cell ) {

  cell.WeightF[0][0] = 0.10;
  cell.WeightF[0][1] = 0.70;
  cell.WeightF[0][2] = 0.45;
  cell.BiasF = 0.15;

  cell.WeightI[0][0] = 0.80;
  cell.WeightI[0][1] = 0.95;
  cell.WeightI[0][2] = 0.80;
  cell.BiasI = 0.65;

  cell.WeightC[0][0] = 0.15;
  cell.WeightC[0][1] = 0.45;
  cell.WeightC[0][2] = 0.25;
  cell.BiasC = 0.20;

  cell.WeightO[0][0] = 0.25;
  cell.WeightO[0][1] = 0.60;
  cell.WeightO[0][2] = 0.40;
  cell.BiasO = 0.10;

}
int main() {

  lstm::lstm_cell cell( 2, 1 );
  init( cell );

  lstm::vector input( 2 );
  input[0] = 1;
  input[1] = 2;
  cell.SetInput( input );
  cell.Activate();
  input[0] = 0.5;
  input[1] = 3;
  cell.SetInput( input );
  cell.Activate();





  std::cin.get();

  clock_t start = clock();

  for ( int i = 0; i < 1000; i++ ) {
    cell.Activate();
  }

  clock_t stop = clock();

  std::cout << ( difftime( stop, start ) ) << '\n';

  //std::cin.get();
  return 0;
}