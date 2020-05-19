#include "matrix.h"

namespace lstm
{
  void matrix::deleteData() {

    for ( int i = 0; i < _rows; i++ ) {
      _data[i].~vector();
    }
    //Why do I need to cast this as void* to work?
    delete[] (void*)_data;
  }

  matrix::matrix( size_t rows, size_t columns ) {
    _rows = rows;
    _columns = columns;
    _data = ( vector* ) operator new[]( sizeof( vector )* rows );
    for ( int i = 0; i < rows; i++ ) {
      new ( _data + i ) vector( columns );
    }
  }

  matrix::matrix( const matrix& other ) {
    _rows = other._rows;
    _columns = other._columns;
    _data = ( vector* ) operator new[]( sizeof( vector )* _rows );
    for ( int i = 0; i < other._rows; i++ ) {
      new ( _data + i ) vector( other._columns );
      std::memcpy( (*this)[i]._data, other[i]._data, _columns * sizeof( double ) );
    }
  }

  matrix::matrix( matrix&& other ) noexcept {
    _rows = other._rows;
    _columns = other._columns;
    _data = other._data;
    other._rows = 0;
    other._columns = 0;
    other._data = nullptr;
  }

  matrix::~matrix() {
    deleteData();
  }

  matrix& matrix::operator=( const matrix& other ) {
    if ( this != &other ) {
      deleteData();
      _rows = other._rows;
      _columns = other._columns;
      _data = ( vector* ) operator new[]( sizeof( vector )* _rows );
      for ( int i = 0; i < other._rows; i++ ) {
        new ( _data + i ) vector( other._columns );
        std::memcpy( (*this)[i]._data, other[i]._data, _columns * sizeof( double ) );
      }
    }
    return *this;
  }

  matrix& matrix::operator=( matrix&& other ) noexcept {
    deleteData();
    _rows = other._rows;
    _columns = other._columns;
    _data = other._data;
    other._rows = 0;
    other._columns = 0;
    other._data = nullptr;
    return *this;
  }

  matrix matrix::operator*( const matrix& rhMat ) const {
    assert( _columns == rhMat.rows() );
    matrix ret( _rows, rhMat.columns() );
    for ( int rowI = 0; rowI < ret.rows(); rowI++ ) {
      for ( int colI = 0; colI < ret[rowI].size(); colI++ ) {
        ret[rowI][colI] = _data[rowI].dotproduct( rhMat.columnVector(colI) );
      }
    }
    return ret;
  }

  vector matrix::operator*( const vector& rhVec ) const {
    assert( _columns == rhVec.size() );
    vector ret( _rows );
    for ( int i = 0; i < _rows; i++ ) {
      ret[i] = _data[i].dotproduct( rhVec );
    }
    return ret;
  }

  vector& matrix::operator[]( size_t pos ) {
    assert( pos < _rows );
    return _data[pos];
  }

  const vector& matrix::operator[]( size_t pos ) const {
    assert( pos < _rows );
    return _data[pos];
  }

  size_t matrix::rows() const {
    return _rows;
  }

  size_t matrix::columns() const {
    return _columns;
  }

  vector matrix::columnVector( size_t col ) const {
    assert( col < _columns );
    vector ret( _rows );
    for ( int i = 0; i < _rows; i++ ) {
      ret[i] = _data[i][col];
    }
    return ret;
  }

}
