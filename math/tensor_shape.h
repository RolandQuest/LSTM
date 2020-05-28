#ifndef TENSOR_SHAPE_H
#define TENSOR_SHAPE_H

#include <initializer_list>
#include <cstdint>

using std::int32_t;

namespace ml
{
  ///
  /// Basic meta-information for storing the shape of a tensor.
  /// A tensor is a block of contiguous memory partitioned in a particular way.
  /// 
  /// _____________________
  ///|                     |
  ///|      Dimension 1    |
  ///|      Element 1      |
  ///|                     |
  ///|____________________ |
  ///|                     |
  ///|      Dimension 1    |
  ///|      Element 2      |
  ///|                     |
  ///|____________________ |
  /// shape => { 2 }
  ///
  /// If the outer dimension has multiple elements, then the entire memory space is divided
  /// equally. For lower dimensions, each element of the outer dimension is further
  /// divided accordingly.
  /// 
  /// _____________________
  ///|     Dim:2 Elem:1    |<--- Start of Dimension 1, Element 1
  ///|_____________________|
  ///|     Dim:2 Elem:2    |
  ///|_____________________|
  ///|     Dim:2 Elem:3    |
  ///|_____________________|
  ///|     Dim:2 Elem:1    |<--- Start of Dimension 1, Element 2
  ///|_____________________|
  ///|     Dim:2 Elem:2    |
  ///|_____________________|
  ///|     Dim:2 Elem:3    |
  ///|_____________________|
  /// shape => { 2, 3 }
  ///
  class tensor_shape
  {

  private:

    int32_t* _shape = nullptr;
    int32_t* _elementSizes = nullptr;
    int32_t _dimensions = 0;

  public:

    //! Empty shape.
    tensor_shape() = default;

    //! Creates a shape with given input.
    tensor_shape( std::initializer_list<int32_t> shape );

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
    int dimensions() const;

    //! Returns the number of elements in a dimension.
    int elementCount(int dimension) const;

    //! Returns the size of an element for a dimension.
    int elementSize( int dimension ) const;

  };
}

#endif