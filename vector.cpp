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
    _data = other._data;
    _dimensions = other._dimensions;
    other._data = nullptr;
    other._dimensions = 0;
  }
  
  vector::~vector() {
    delete[] _data;
  }

  vector& vector::operator=( const vector& other ) {
    if ( &other != this ) {
      delete[] _data;
      _dimensions = other._dimensions;
      _data = new double[_dimensions];
      std::memcpy( _data, other._data, _dimensions * sizeof( double ) );
    }
    return *this;
  }
  
  vector& vector::operator=( vector&& other ) noexcept {
    delete[] _data;
    _data = other._data;
    _dimensions = other._dimensions;
    other._data = nullptr;
    other._dimensions = 0;
    return *this;
  }
  
  vector vector::operator+( const vector& other ) const  {
    assert( _dimensions == other.size() );
    vector ret( _dimensions );
    for ( int i = 0; i < _dimensions; i++ ) {
      ret[i] = _data[i] + other.at( i );
    }
    return ret;
  }

  vector vector::operator+( const double& val ) const  {
    vector ret( _dimensions );
    for ( int i = 0; i < _dimensions; i++ ) {
      ret[i] = _data[i] + val;
    }
    return ret;
  }

  vector vector::operator*( const vector& other ) const {
    assert( _dimensions == other.size() );
    vector ret( _dimensions );
    for ( int i = 0; i < _dimensions; i++ ) {
      ret[i] = _data[i] * other.at( i );
    }
    return ret;
  }

  vector vector::operator*( const double& val ) const {
    vector ret( _dimensions );
    for ( int i = 0; i < _dimensions; i++ ) {
      ret[i] = _data[i] * val;
    }
    return ret;
  }

  double& vector::operator[]( size_t pos ) {
    assert( pos < _dimensions );
    return _data[pos];
  }

  vector vector::sub( size_t offset, size_t dimensions ) const {
    assert( offset + dimensions <= _dimensions );
    vector ret( dimensions );
    std::memcpy( ret._data, _data + offset, dimensions * sizeof( double ) );
    return ret;
  }

  vector vector::append( vector& other ) const {
    vector ret( _dimensions + other._dimensions );
    std::memcpy( ret._data, _data, _dimensions * sizeof( double ) );
    std::memcpy( ret._data + _dimensions, other._data, other._dimensions * sizeof( double ) );
    return ret;
  }

  size_t vector::size() const {
    return _dimensions;
  }

  double vector::at( size_t pos ) const {
    assert( pos < _dimensions );
    return _data[pos];
  }

  double vector::dotproduct( const vector& other ) const {
    assert( size() == other.size() );
    double ret = 0.0;
    for ( int i = 0; i < _dimensions; i++ ) {
      ret += _data[i] * other.at(i);
    }
    return ret;
  }

}
