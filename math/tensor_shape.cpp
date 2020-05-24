#include "tensor_shape.h"

#include <memory>
#include <assert.h>

namespace ml
{

  tensor_shape::tensor_shape(std::initializer_list<int> shape) {

    _dimensions = shape.size();
    _shape = new int[_dimensions];

    auto start = std::begin( shape );
    for ( int i = 0; i < _dimensions; i++ ) {
      _shape[i] = *( start + i );
    }
  }

  tensor_shape::tensor_shape( const tensor_shape& other ) {
    _dimensions = other._dimensions;
    _shape = new int[_dimensions];
    std::copy( other._shape, other._shape + _dimensions, _shape );
  }

  tensor_shape::tensor_shape( tensor_shape&& other ) noexcept {
    _dimensions = other._dimensions;
    _shape = other._shape;
    other._shape = nullptr;
  }

  tensor_shape::~tensor_shape() {
    delete[] _shape;
  }

  tensor_shape& tensor_shape::operator=( const tensor_shape& other ) {
    if ( this != &other ) {
      delete[] _shape;
      _dimensions = other._dimensions;
      _shape = new int[_dimensions];
      std::copy( other._shape, other._shape + _dimensions, _shape );
    }
    return *this;
  }

  tensor_shape& tensor_shape::operator=( tensor_shape&& other ) noexcept {
    delete[] _shape;
    _dimensions = other._dimensions;
    _shape = other._shape;
    other._shape = nullptr;
    return *this;
  }

  int tensor_shape::size() const {
    return _dimensions;
  }

  int tensor_shape::dimensionSize( int dimension ) const {
    assert( dimension < _dimensions );
    return _shape[dimension];
  }

  int tensor_shape::operator[]( int dimension ) const {
    assert( dimension < _dimensions );
    return _shape[dimension];
  }
}