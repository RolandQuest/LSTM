#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>

#include "vector.h"

namespace ml
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

		//! Creates an empty matrix.
		matrix() = default;

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

		//! Accesses a row.
		vector& operator[]( size_t pos );

		//! Accesses a row.
		const vector& operator[]( size_t pos ) const;


		//! Returns the number of rows.
		size_t rows() const;

		//! Returns the number of columns.
		size_t columns() const;

		//! Creates a vector for a column.
		vector columnVector( size_t col ) const;

		//! Transposes the matrix.
		matrix& transpose();

	};

	matrix transpose( const matrix& mat );
	matrix operator*( const matrix& lhm, const matrix& rhm );
	vector operator*( const matrix& mat, const vector& vec );
	vector operator*( const vector& vec, const matrix& mat );

}







#endif