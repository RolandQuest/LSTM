#include "vector.h"

#include <math.h>

namespace ml
{
  vector::vector( size_t dimensions ) {
    _dimensions = dimensions;
    _data = new double[dimensions];
    std::memset( _data, 0, dimensions * sizeof( double ) );
  }

  vector::vector( std::initializer_list<double> elems ) {
    _dimensions = elems.size();
    _data = new double[_dimensions];
    auto start = std::begin( elems );
    for ( int i = 0; i < _dimensions; i++ ) {
      _data[i] = *( start + i );
    }
  }

  vector::vector( const vector& other ) {
    _dimensions = other._dimensions;
    _data = new double[_dimensions];
    std::memcpy( _data, other._data, _dimensions * sizeof( double ) );
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
    if ( this != &other ) {
      delete[] _data;
      _data = other._data;
      _dimensions = other._dimensions;
      other._data = nullptr;
      other._dimensions = 0;
    }
    return *this;
  }

  vector& vector::operator+=( const vector& other ) {
    assert( _dimensions == other.size() );
    for ( int i = 0; i < _dimensions; i++ ) {
      _data[i] += other[i];
    }
    return *this;
  }

  vector& vector::operator+=( const double& val ) {
    for ( int i = 0; i < _dimensions; i++ ) {
      _data[i] += val;
    }
    return *this;
  }

  vector& vector::operator-=( const vector& other ) {
    assert( _dimensions == other.size() );
    for ( int i = 0; i < _dimensions; i++ ) {
      _data[i] -= other[i];
    }
    return *this;
  }

  vector& vector::operator-=( const double& val ) {
    for ( int i = 0; i < _dimensions; i++ ) {
      _data[i] -= val;
    }
    return *this;
  }

  vector& vector::operator*=( const vector& other ) {
    assert( _dimensions == other.size() );
    for ( int i = 0; i < _dimensions; i++ ) {
      _data[i] *= other[i];
    }
    return *this;
  }

  vector& vector::operator*=( const double& val ) {
    for ( int i = 0; i < _dimensions; i++ ) {
      _data[i] *= val;
    }
    return *this;
  }

  vector& vector::operator/=( const vector& other ) {
    assert( _dimensions == other.size() );
    for ( int i = 0; i < _dimensions; i++ ) {
      _data[i] /= other[i];
    }
    return *this;
  }

  vector& vector::operator/=( const double& val ) {
    for ( int i = 0; i < _dimensions; i++ ) {
      _data[i] /= val;
    }
    return *this;
  }

  double& vector::operator[]( size_t pos ) {
    assert( pos < _dimensions );
    return _data[pos];
  }

  const double& vector::operator[]( size_t pos ) const {
    assert( pos < _dimensions );
    return _data[pos];
  }

  vector vector::sub( size_t offset, size_t dimensions ) const {
    assert( offset + dimensions <= _dimensions );
    vector ret( dimensions );
    std::memcpy( ret._data, _data + offset, dimensions * sizeof( double ) );
    return ret;
  }

  vector vector::append( const vector& other ) const {
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
      ret += _data[i] * other[i];
    }
    return ret;
  }

  double vector::sum() const {
    double sum = 0.0;
    for ( int i = 0; i < _dimensions; i++ ) {
      sum += _data[i];
    }
    return sum;
  }

  ///
  /// Math operators
  ///

  //Addition
  vector operator+( const vector& lhs, const vector& rhs ) {
    assert( lhs.size() == rhs.size() );
    vector ret( lhs.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = lhs[i] + rhs[i];
    }
    return ret;
  }
  vector operator+( const double& val, const vector& rhs ) {
    vector ret( rhs.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = val + rhs[i];
    }
    return ret;
  }
  vector operator+( const vector& lhs, const double& val ) {
    vector ret( lhs.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = lhs[i] + val;
    }
    return ret;
  }
  //Subtraction
  vector operator-( const vector& lhs, const vector& rhs ) {
    assert( lhs.size() == rhs.size() );
    vector ret( lhs.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = lhs[i] - rhs[i];
    }
    return ret;
  }
  vector operator-( const double& val, const vector& rhs ) {
    vector ret( rhs.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = val - rhs[i];
    }
    return ret;
  }
  vector operator-( const vector& lhs, const double& val ) {
    vector ret( lhs.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = lhs[i] - val;
    }
    return ret;
  }
  //Multiplication
  vector operator*( const vector& lhs, const vector& rhs ) {
    assert( lhs.size() == rhs.size() );
    vector ret( lhs.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = lhs[i] * rhs[i];
    }
    return ret;
  }
  vector operator*( const double& val, const vector& rhs ) {
    vector ret( rhs.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = val * rhs[i];
    }
    return ret;
  }
  vector operator*( const vector& lhs, const double& val ) {
    vector ret( lhs.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = lhs[i] * val;
    }
    return ret;
  }
  //Division
  vector operator/( const vector& lhs, const vector& rhs ) {
    assert( lhs.size() == rhs.size() );
    vector ret( lhs.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = lhs[i] / rhs[i];
    }
    return ret;
  }
  vector operator/( const double& val, const vector& rhs ) {
    vector ret( rhs.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = val / rhs[i];
    }
    return ret;
  }
  vector operator/( const vector& lhs, const double& val ) {
    vector ret( lhs.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = lhs[i] / val;
    }
    return ret;
  }

  ///
  /// Math functions
  ///

  vector pow( const vector& vec, const double& val ) {
    vector ret( vec.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = ::pow( vec[i], val );
    }
    return ret;
  }
  vector exp( const vector& vec ) {
    vector ret( vec.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = ::exp( vec[i] );
    }
    return ret;
  }
  vector sigmoid( const vector& vec ) {
    return 1 / ( 1 + exp( -1 * vec ) );
  }
  vector sigmoid_d( const vector& vec ) {
    vector sig = sigmoid( vec );
    return sig * ( 1 - sig );
  }
  vector tanh( const vector& vec ) {
    vector e2 = pow( exp( vec ), 2 );
    return ( e2 - 1 ) / ( e2 + 1 );
  }
  vector tanh_d( const vector& vec ) {
    return 1 - pow( vec, 2 );
  }
  vector softmax( const vector& vec ) {
    vector ret = exp( vec );
    ret /= ret.sum();
    return ret;
  }
  vector softmax_d( const vector& vec ) {

    vector e = exp( vec );
    double sum = e.sum();
    e /= ::pow( sum, 2 );

    vector ret( vec.size() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = e[i] * ( sum - e[i] );
    }

    return ret;
  }

}
