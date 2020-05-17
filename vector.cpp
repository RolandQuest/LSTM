#include "vector.h"

namespace lstm
{
  vector::vector( size_t dimensions ) {
    _dimensions = dimensions;
    _data = new double[dimensions];
    std::memset( _data, 0, dimensions * sizeof( double ) );
  }

  vector::vector( const vector& other ) {

    if ( this != &other ) {
      _dimensions = other._dimensions;
      _data = new double[_dimensions];
      std::memcpy( _data, other._data, _dimensions * sizeof( double ) );
    }
  }

  vector::vector( vector&& other ) noexcept {

    if ( _children == 0 ) {
      if ( this == _parent ) {
        delete[] _data;
      }
      _parent = this;
      _data = other._data;
      _dimensions = other._dimensions;
      other._data = nullptr;
      other._dimensions = 0;
    }
  }

  vector& vector::operator=( const vector& other ) {

    if ( &other != this ) {
      _dimensions = other._dimensions;
      delete[] _data;
      _data = new double[_dimensions];
      for ( int i = 0; i < _dimensions; i++ ) {
        _data[i] = other.at( i );
      }
    }
    return *this;
  }

  vector::~vector() {
    if ( _parent == this ) {
      delete[] _data;
    }
  }

  size_t vector::size() const {
    return _dimensions;
  }

  double& vector::operator[]( size_t pos ) {
    assert( pos < _dimensions );
    return _data[pos];
  }

  double vector::at( size_t pos ) const {
    assert( pos < _dimensions );
    return _data[pos];
  }
}



vector::vector( vector& other, size_t offset, size_t dimensions ) {
  assert( offset + dimensions <= other.size() );
  _dimensions = dimensions;
  _data = other._data + offset;
}
