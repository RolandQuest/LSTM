#ifndef LSTM_H
#define LSTM_H

#include <math.h>

#include "matrix.h"

namespace lstm
{
  double sigmoid( double val ) {
    return 1 / ( 1 + exp( -val ) );
  }
  double tanh( double val ) {
    double e2 = pow( exp( val ), 2 );
    return ( e2 - 1 ) / ( e2 + 1 );
  }
  vector activate( double( *foo )( double ), const vector& vec ) {
    vector ret( vec.size() );
    for ( size_t i = 0; i < vec.size(); i++ ) {
      ret[i] = foo( vec.at( i ) );
    }
    return ret;
  }


  class lstm_cell {

  private:

    vector* Xt;
    vector* Ht;
    vector* Ct;

    matrix* WeightF;
    matrix* WeightI;
    matrix* WeightC;
    matrix* WeightO;

  public:

    lstm_cell( size_t iSize, size_t oSize ) {

      Xt = new vector( iSize );
      Ht = new vector( oSize );
      Ct = new vector( oSize );

      WeightF = new matrix( oSize, iSize + oSize );
      WeightI = new matrix( oSize, iSize + oSize );
      WeightC = new matrix( oSize, iSize + oSize );
      WeightO = new matrix( oSize, iSize + oSize );
    }

    void SetInput( const vector& input ) {
      for ( size_t i = 0; i < Xt->size(); i++ ) {
        Xt[i] = input.at( i );
      }
    }

    void Activate() {

      vector HtXt = Ht->append( *Xt );
      vector ft = activate( &sigmoid, *WeightF * HtXt );
      vector it = activate( &tanh, *WeightC * HtXt );
      vector ct = activate( &tanh, *WeightI * HtXt );
      vector ot = activate( &sigmoid, *WeightO * HtXt );

      *Ct = *Ct * ft + ct * it;
      *Ht = activate( &tanh, *Ct ) * ot;
    }

  };

}







#endif