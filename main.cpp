#include <iostream>
#include <time.h>

#include "layers/lstm.h"
#include "math/matrix.h"
#include "math/vector.h"

#include "math/trainable_matrix.h"
#include "math/tensor.h"



void init( ml::lstm& cell ) {

  cell.Uf[0][0] = 0.10;
  cell.Wf[0][0] = 0.70;
  cell.Wf[0][1] = 0.45;
  cell.BiasF = 0.15;

  cell.Ui[0][0] = 0.80;
  cell.Wi[0][0] = 0.95;
  cell.Wi[0][1] = 0.80;
  cell.BiasI = 0.65;

  cell.Uc[0][0] = 0.15;
  cell.Wc[0][0] = 0.45;
  cell.Wc[0][1] = 0.25;
  cell.BiasC = 0.20;

  cell.Uo[0][0] = 0.25;
  cell.Wo[0][0] = 0.60;
  cell.Wo[0][1] = 0.40;
  cell.BiasO = 0.10;

}

ml::trainable_matrix GetMat() {

  ml::trainable_matrix m( 3, 2, false );
  return m;
}



int main() {


  ml::tensor t = { 3, 3, 1, 9 };




  ml::lstm cell( 2, 1 );
  init( cell );

  ml::vector input( 2 );
  input[0] = 1;
  input[1] = 2;
  //cell.SetInput( input );
  //cell.Activate();
  input[0] = 0.5;
  input[1] = 3;
  //cell.SetInput( input );
  //cell.Activate();





  std::cin.get();

  clock_t start = clock();

  for ( int i = 0; i < 1000; i++ ) {
    //cell.Activate();
  }

  clock_t stop = clock();

  std::cout << ( difftime( stop, start ) ) << '\n';

  //std::cin.get();
  return 0;
}