#ifndef ml_H
#define ml_H

#include <math.h>

#include "ilayer.h"
#include "../math/trainable_matrix.h"

namespace ml
{

  struct timestep_meta {
    vector Eht, Ext, Ect;
    vector ft, it, ct, ot;
    vector xt, ht;
  };

  class lstm : public ilayer {

  public:
  //private:

    vector Xt;
    vector Ht;
    vector Ct;

    trainable_matrix Wf;
    trainable_matrix Wi;
    trainable_matrix Wc;
    trainable_matrix Wo;

    trainable_matrix Uf;
    trainable_matrix Ui;
    trainable_matrix Uc;
    trainable_matrix Uo;

    double BiasF = 0.0;
    double BiasI = 0.0;
    double BiasC = 0.0;
    double BiasO = 0.0;

  public:

    //! Basic constructor.
    lstm( size_t iSize, size_t oSize );

    //! Basic destructor.
    virtual ~lstm() = default;

    ///
    /// ilayer
    ///

    //! Returns the size of the input vector expected.
    size_t inputSize() const;

    //! Returns the size of the output vector.
    size_t outputSize() const;

    //! Sets the input used when activate() is called.
    void setInput( const vector& input );

    //! Returns the output vector.
    const vector& getOutput() const;

    //! Activates the network.
    void activate();

    //! Passes error from later layers to train on.
    void learn( const vector& error, double learningRate );

    //! Used in case of doing batch learning.
    void applyLearnings();

  };

}







#endif