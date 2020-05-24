#ifndef TRAINABLE_MATRIX
#define TRAINABLE_MATRIX

#include "matrix.h"

namespace ml
{
  //! Matrix wrapper that stores error information for batching.
  class trainable_matrix : public matrix
  {

  private:

    matrix _errorMatrix;
    bool _isTrainable = true;

  public:

    trainable_matrix() = default;

    trainable_matrix( size_t rows, size_t columns, bool trainable = true );

    trainable_matrix( const trainable_matrix& other );

    trainable_matrix( trainable_matrix&& other ) noexcept;

    virtual ~trainable_matrix() = default;

    //! Assignment operator.
    trainable_matrix& operator=( const trainable_matrix& other );

    //! Move assignment operator.
    trainable_matrix& operator=( trainable_matrix&& other ) noexcept;



    bool isTrainable() const;

    void setTrainable( bool trainable );

    void addError( const matrix& errorMat );

    void applyError();

  };

}

#endif