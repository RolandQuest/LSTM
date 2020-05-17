#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>

#include "vector.h"

namespace lstm
{

	///
	/// A simple matrix with static size.
	/// Each row is a vector.
	///
	class matrix
	{

	private:

		vector* _data = nullptr;
		size_t _rows = 0;
		size_t _columns = 0;

		void deleteData();

	public:

		//! Creates a square matrix with given size.
		matrix( size_t rows, size_t columns );

		//! Copy constructor.
		matrix( const matrix& other );

		//! Move constructor.
		matrix( matrix&& other ) noexcept;

		//! Basic destructor.
		virtual ~matrix();


		//! Assignment operator.
		matrix& operator=( const matrix& other );

		//! Move assignment operator.
		matrix& operator=( matrix&& other ) noexcept;

		//! Standard matrix multiplication.
		matrix operator*( const matrix& rhMat ) const;

		//! Matrix multiplied by vector.
		vector operator*( const vector& rhVec ) const;

		//! Accesses a row.
		vector& operator[]( size_t pos );


		//! Returns the number of rows.
		size_t rows() const;

		//! Returns the number of columns.
		size_t columns() const;

		//! Creates a vector for a column.
		vector columnVector( size_t col ) const;

	};

}







#endif