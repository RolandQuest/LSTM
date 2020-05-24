#include "trainable_matrix.h"

namespace ml
{

  trainable_matrix::trainable_matrix( size_t rows, size_t columns, bool trainable ) : matrix( rows, columns ) {
    _errorMatrix = matrix( rows, columns );
    _isTrainable = trainable;
  }

  trainable_matrix::trainable_matrix( const trainable_matrix& other ) : matrix( other ) {
    _errorMatrix = other._errorMatrix;
    _isTrainable = other._isTrainable;
  }

  trainable_matrix::trainable_matrix( trainable_matrix&& other ) noexcept : matrix( std::move(other) ) {
    _errorMatrix = std::move( other._errorMatrix );
    _isTrainable = other._isTrainable;
  }

  trainable_matrix& trainable_matrix::operator=( const trainable_matrix& other ) {

    if ( this != &other ) {
      matrix::operator=( other );
      _errorMatrix = other._errorMatrix;
      _isTrainable = other._isTrainable;
    }
    return *this;
  }

  trainable_matrix& trainable_matrix::operator=( trainable_matrix&& other ) noexcept {
    matrix::operator=( std::move(other) );
    _errorMatrix = std::move( other._errorMatrix );
    _isTrainable = other._isTrainable;
    return *this;
  }

  bool trainable_matrix::isTrainable() const {
    return _isTrainable;
  }

  void trainable_matrix::setTrainable( bool trainable ) {
    _isTrainable = trainable;
  }

  void trainable_matrix::addError( const matrix& errorMat ) {
    assert( errorMat.rows() == _errorMatrix.rows() );
    assert( errorMat.columns() == _errorMatrix.columns() );

    for ( int i = 0; i < errorMat.rows(); i++ ) {
      for ( int j = 0; j < errorMat.columns(); j++ ) {
        _errorMatrix[i][j] += errorMat[i][j];
      }
    }
  }

  void trainable_matrix::applyError() {

    for ( int i = 0; i < _errorMatrix.rows(); i++ ) {
      for ( int j = 0; j < _errorMatrix.columns(); j++ ) {
        (*this)[i][j] += _errorMatrix[i][j];
        _errorMatrix[i][j] = 0.0;
      }
    }
  }


}