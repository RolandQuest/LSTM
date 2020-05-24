#ifndef TENSOR_SHAPE_H
#define TENSOR_SHAPE_H

#include <initializer_list>

namespace ml
{
  //! Basic meta-information for storing the shape of a tensor.
  class tensor_shape
  {

  private:

    int* _shape = nullptr;
    int _dimensions = 0;

  public:

    //! Empty shape.
    tensor_shape() = default;

    //! Creates a shape with given input.
    tensor_shape( std::initializer_list<int> shape );

    //! Copy constructor.
    tensor_shape( const tensor_shape& other );

    //! Move constructor.
    tensor_shape( tensor_shape&& other ) noexcept;

    //! Destructor.
    virtual ~tensor_shape();

    //! Assignment copy operator.
    tensor_shape& operator=( const tensor_shape& other );

    //! Assignment move operator.
    tensor_shape& operator=( tensor_shape&& other ) noexcept;

    //! Returns the number of dimensions of the shape.
    int size() const;

    //! Returns the size of a dimension.
    int dimensionSize(int dimension) const;

    //! Returns the size of a dimension.
    int operator[]( int dimension ) const;
  };
}

#endif