#include "matrix.h"

namespace ml
{
  void swap( matrix& mat1, matrix& mat2 ) {

    using std::swap;
    swap( mat1._data, mat2._data );
    swap( mat1._rows, mat2._rows );
    swap( mat1._columns, mat2._columns );
  }

  void matrix::createData( size_t rows, size_t columns ) {
    _rows = rows;
    _columns = columns;
    _data = ( vector* ) operator new[]( sizeof( vector )* rows );
    for ( int i = 0; i < rows; i++ ) {
      new ( _data + i ) vector( columns );
    }
  }

  void matrix::deleteData() {

    for ( int i = 0; i < _rows; i++ ) {
      _data[i].~vector();
    }
    //Why do I need to cast this as void* to work?
    delete[] (void*)_data;
  }

  matrix::matrix( size_t rows, size_t columns ) {
    createData( rows, columns );
  }

  matrix::matrix( const matrix& other ) {

    createData( other._rows, other._columns );

    for ( int i = 0; i < other._rows; i++ ) {
      std::copy(other[i]._data, other[i]._data + other[i]._dimensions, (*this)[i]._data );
    }
  }

  matrix::matrix( matrix&& other ) noexcept {
    swap( *this, other );
  }

  matrix::~matrix() {
    deleteData();
  }

  matrix& matrix::operator=( const matrix& other ) {
    matrix temp( other );
    swap( *this, temp );
    return *this;
  }

  matrix& matrix::operator=( matrix&& other ) noexcept {
    swap( *this, other );
    return *this;
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

  matrix& matrix::transpose() {
    *this = ml::transpose( *this );
    return *this;
  }

  matrix transpose( const matrix& mat ) {
    matrix ret( mat.columns(), mat.rows() );
    for ( int rowI = 0; rowI < ret.rows(); rowI++ ) {
      for ( int colI = 0; colI < ret[rowI].size(); colI++ ) {
        ret[rowI][colI] = mat[colI][rowI];
      }
    }
    return ret;
  }

  matrix operator*( const matrix& lhm, const matrix& rhm ) {
    assert( lhm.columns() == rhm.rows() );
    matrix ret( lhm.rows(), rhm.columns() );
    for ( int rowI = 0; rowI < ret.rows(); rowI++ ) {
      for ( int colI = 0; colI < ret[rowI].size(); colI++ ) {
        ret[rowI][colI] = lhm[rowI].dotproduct( rhm.columnVector( colI ) );
      }
    }
    return ret;
  }

  vector operator*( const matrix& mat, const vector& vec ) {
    assert( mat.columns() == vec.size() );
    vector ret( mat.rows() );
    for ( int i = 0; i < ret.size(); i++ ) {
      ret[i] = mat[i].dotproduct( vec );
    }
    return ret;
  }

  vector operator*( const vector& vec, const matrix& mat ) {
    return mat * vec;
  }

}
