#ifndef LSTM_VECTOR_H
#define LSTM_VECTOR_H

#include <assert.h>
#include <memory>

namespace lstm {

  ///
  /// A vector of doubles.
  /// A vector can share its data with other vectors so care must be taken
  /// to ensure only the master pointer is deleted when destructors are called.
  /// Size of the vector is set upon creation. It is not dynamic.
  ///
  class vector
  {

  private:

    double* _data = nullptr;
    size_t _dimensions = 0;
    vector* _parent = this;
    int _children = 0;

  public:

    //! Creates a vector filled with 0's.
    vector( size_t dimensions );

    //! Copy constructor.
    vector( const vector& other );

    //! Move constructor
    vector( vector&& other ) noexcept;

    //! Frees memory.
    virtual ~vector();


    //! 
    vector& operator=( const vector& other );

    //! Returns reference to the data at given position.
    double& operator[]( size_t pos );


    //! Creates a subvector.
    vector& sub( size_t offset, size_t dimensions ) const;

    //! Appends the vector onto the current vector.
    vector& append( vector& other );

    //! Returns the dimensions of this vector.
    size_t size() const;

    //! Returns a copy of the double at given position.
    double at( size_t pos ) const;

  };

}

#endif