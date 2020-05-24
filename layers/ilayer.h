#ifndef ILAYER_H
#define ILAYER_H

#include "../math/vector.h"

namespace ml
{
  class ilayer
  {

  private:

  public:

    //! Returns the size of the input vector expected.
    virtual size_t inputSize() const = 0;

    //! Returns the size of the output vector.
    virtual size_t outputSize() const = 0;

    //! Sets the input used when activate() is called.
    virtual void setInput( const vector& input ) = 0;

    //! Returns the output vector.
    virtual const vector& getOutput() const = 0;

    //! Activates the network.
    virtual void activate() = 0;

    //! Passes error from later layers to train on.
    virtual void learn( const vector& error, double learningRate ) = 0;

    //! Used in case of doing batch learning.
    virtual void applyLearnings() = 0;


  };
}

#endif