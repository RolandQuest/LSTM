#include "tensor_shape.h"

#include <memory>
#include <assert.h>

namespace ml
{

  tensor_shape::tensor_shape(std::initializer_list<int> shape) {

    _dimensions = shape.size();
    _shape = new int[_dimensions];
    _elementSizes = new int[_dimensions];

    auto start = std::begin( shape );
    for ( int i = _dimensions - 1; i >= 0; i-- ) {
      _shape[i] = *( start + i );

      if ( i == _dimensions - 1 ) {
        _elementSizes[i] = 1;
      }
      else {
        _elementSizes[i] = _elementSizes[i + 1] * _shape[i + 1];
      }
    }
  }

  tensor_shape::tensor_shape( const tensor_shape& other ) {
    _dimensions = other._dimensions;
    _shape = new int[_dimensions];
    _elementSizes = new int[_dimensions];
    std::copy( other._shape, other._shape + _dimensions, _shape );
    std::copy( other._elementSizes, other._elementSizes + _dimensions, _elementSizes );
  }

  tensor_shape::tensor_shape( tensor_shape&& other ) noexcept {
    _dimensions = other._dimensions;
    _shape = other._shape;
    _elementSizes = other._elementSizes;
    other._shape = nullptr;
    other._elementSizes = nullptr;
  }

  tensor_shape::~tensor_shape() {
    delete[] _shape;
    delete[] _elementSizes;
  }

  tensor_shape& tensor_shape::operator=( const tensor_shape& other ) {
    if ( this != &other ) {
      delete[] _shape;
      delete[] _elementSizes;
      _dimensions = other._dimensions;
      _shape = new int[_dimensions];
      _elementSizes = new int[_dimensions];
      std::copy( other._shape, other._shape + _dimensions, _shape );
      std::copy( other._elementSizes, other._elementSizes + _dimensions, _elementSizes );
    }
    return *this;
  }

  tensor_shape& tensor_shape::operator=( tensor_shape&& other ) noexcept {
    delete[] _shape;
    delete[] _elementSizes;
    _dimensions = other._dimensions;
    _shape = other._shape;
    _elementSizes = other._elementSizes;
    other._shape = nullptr;
    other._elementSizes = nullptr;
    return *this;
  }

  int tensor_shape::dimensions() const {
    return _dimensions;
  }

  int tensor_shape::elementCount( int dimension ) const {
    assert( dimension < _dimensions );
    return _shape[dimension];
  }

  int tensor_shape::elementSize( int dimension ) const {
    assert( dimension < _dimensions );
    return _elementSizes[dimension];
  }
}