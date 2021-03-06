#include "tensor.h"

#include <memory>
#include <assert.h>

namespace ml
{

  int tensor::calculateOffset( std::initializer_list<int> indices ) {
    int offset = 0;
    auto start = indices.begin();
    for ( int i = 0; i < indices.size(); i++ ) {
      offset += *(start + i) * _shape.elementSize( i );
    }
    return offset;
  }

  tensor::tensor( std::initializer_list<int> shape ) {

    _totalDoubles = 1;
    for ( auto& entry : shape ) {
      _totalDoubles *= entry;
    }
    _shape = tensor_shape( shape );
    _data = new double[_totalDoubles];
    std::memset( _data, 0, _totalDoubles * sizeof( double ) );
  }

  tensor::tensor( const tensor& other ) {
    _shape = other._shape;
    _totalDoubles = other._totalDoubles;
    _data = new double[_totalDoubles];
    std::copy( other._data, other._data + _totalDoubles, _data );
  }

  tensor::tensor( tensor&& other ) noexcept {
    _data = other._data;
    _shape = std::move( other._shape );
    _totalDoubles = other._totalDoubles;
    other._data = nullptr;
    other._totalDoubles = 0;
  }

  tensor& tensor::operator=( const tensor& other ) {

    if ( this != &other ) {
      delete[] _data;
      _shape = other._shape;
      _totalDoubles = other._totalDoubles;
      _data = new double[_totalDoubles];
      std::copy( other._data, other._data + _totalDoubles, _data );
    }
    return *this;
  }

  tensor& tensor::operator=( tensor&& other ) noexcept {
    delete[] _data;
    _data = other._data;
    _shape = std::move( other._shape );
    _totalDoubles = other._totalDoubles;
    other._data = nullptr;
    other._totalDoubles = 0;
    return *this;
  }

  tensor::~tensor() {
    delete[] _data;
  }
}
