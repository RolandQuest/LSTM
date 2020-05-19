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

    //! Creates an empty vector.
    vector() = default;

    //! Creates a vector filled with 0's.
    vector( size_t dimensions );

    //! Creates a vector from initializer list.
    vector( std::initializer_list<double> elems );

    //! Copy constructor.
    vector( const vector& other );

    //! Move constructor
    vector( vector&& other ) noexcept;

    //! Frees memory.
    virtual ~vector();


    //! Assignment operators.
    vector& operator=( const vector& other );
    vector& operator=( vector&& other ) noexcept;
    vector& operator+=( const vector& other );
    vector& operator+=( const double& val );
    vector& operator-=( const vector& other );
    vector& operator-=( const double& val );
    vector& operator*=( const vector& other );
    vector& operator*=( const double& val );
    vector& operator/=( const vector& other );
    vector& operator/=( const double& val );

    //! Returns reference to the data at given position.
    double& operator[]( size_t pos );
    const double& operator[]( size_t pos ) const;

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

    //! Returns the sum of all elements.
    double sum() const;

  };

  // Basic operators.
  vector operator+( const vector& lhs, const vector& rhs );
  vector operator+( const double& val, const vector& rhs );
  vector operator+( const vector& lhs, const double& val );
  vector operator-( const vector& lhs, const vector& rhs );
  vector operator-( const double& val, const vector& rhs );
  vector operator-( const vector& lhs, const double& val );
  vector operator*( const vector& lhs, const vector& rhs );
  vector operator*( const double& val, const vector& rhs );
  vector operator*( const vector& lhs, const double& val );
  vector operator/( const vector& lhs, const vector& rhs );
  vector operator/( const double& val, const vector& rhs );
  vector operator/( const vector& lhs, const double& val );

  //Useful maths.
  vector pow( const vector& x, const double& val );
  vector exp( const vector& x );
  vector sigmoid( const vector& vec );
  vector sigmoid_d( const vector& vec );
  vector tanh( const vector& vec );
  vector tanh_d( const vector& vec );
  vector softmax( const vector& vec );
  vector softmax_d( const vector& vec );
}

#endif