#ifndef LSTM_VECTOR_H
#define LSTM_VECTOR_H

#include <assert.h>
#include <memory>

namespace lstm {

  ///
  /// A vector of doubles.
  /// Size of the vector is set upon creation. It is not dynamic.
  ///
  class vector
  {

    friend class matrix;

  private:

    double* _data = nullptr;
    size_t _dimensions = 0;

  public:

    //! Creates a vector filled with 0's.
    vector( size_t dimensions );

    //! Copy constructor.
    vector( const vector& other );

    //! Move constructor
    vector( vector&& other ) noexcept;

    //! Frees memory.
    virtual ~vector();


    //! Basic assignment operator.
    vector& operator=( const vector& other );

    //! Move assignment operator.
    vector& operator=( vector&& other ) noexcept;

    //! Element-wise addition.
    vector operator+( const vector& other ) const;

    //! Element-wise addition.
    vector operator+( const double& val ) const;

    //! Element-wise multiplication.
    vector operator*( const vector& other ) const;

    //! Element-wise multiplication.
    vector operator*( const double& val ) const;

    //! Returns reference to the data at given position.
    double& operator[]( size_t pos );


    //! Creates a subvector.
    vector sub( size_t offset, size_t dimensions ) const;

    //! Appends the vector onto the current vector.
    vector append( vector& other ) const;

    //! Returns the dimensions of this vector.
    size_t size() const;

    //! Returns a copy of the double at given position.
    double at( size_t pos ) const;

    //! Returns the dot-product of two vectors.
    double dotproduct( const vector& other ) const;

  };

}

#endif