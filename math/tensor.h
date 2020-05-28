#ifndef TENSOR_H
#define TENSOR_H

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
    
    int calculateOffset( std::initializer_list<int> indices );

  public:

    tensor() = default;

    tensor( std::initializer_list<int> shape );

    tensor( const tensor_shape& shape );

    tensor( const tensor& other );

    tensor( tensor&& other ) noexcept;
    
    tensor& operator=( const tensor& other );

    tensor& operator=( tensor&& other ) noexcept;

    virtual ~tensor();

  };
}

#endif