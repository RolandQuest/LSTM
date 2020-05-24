#ifndef TENSOR_H
#define TENSOR_h

#include <initializer_list>

#include "tensor_shape.h"

namespace ml
{

  ///
  /// A tensor with double types.
  ///
  class tensor
  {

  private:

    double* _data = nullptr;
    int _totalDoubles = 0;
    tensor_shape _shape;
    
  public:

    tensor( std::initializer_list<int> shape );

    tensor( const tensor& other );

    tensor( tensor&& other ) noexcept;
    
    tensor& operator=( const tensor& other );

    tensor& operator=( tensor&& other ) noexcept;

    virtual ~tensor();

  };
}

#endif