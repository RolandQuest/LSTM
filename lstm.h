#ifndef LSTM_H
#define LSTM_H

#include <math.h>

#include "matrix.h"

namespace lstm
{

  struct timestep_meta {
    vector Eht, Ext, Ect, Eout;
    vector ft, it, ct, ot;
    vector xt, ht;
  };

  class lstm_cell {

  public:
  //private:

    vector Xt;
    vector Ht;
    vector Ct;

    matrix WeightF;
    matrix WeightI;
    matrix WeightC;
    matrix WeightO;

    double BiasF = 0.0;
    double BiasI = 0.0;
    double BiasC = 0.0;
    double BiasO = 0.0;

  public:

    //! Basic constructor.
    lstm_cell( size_t iSize, size_t oSize );

    //! Basic destructor.
    virtual ~lstm_cell() = default;


    //! Sets the input (Xt).
    void SetInput( const vector& input );

    //! Does a forward passes of the cell.
    void Activate();

  };

}







#endif