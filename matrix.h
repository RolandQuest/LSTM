#ifndef MATRIX_H
#define MATRIX_H

#include <assert.h>

#include "vector.h"

namespace lstm
{

	///
	/// A simple matrix.
	/// Each row is its own vector.
	///
	class matrix
	{

	private:

		vector* _data;
		size_t _rows;
		size_t _columns;

	public:

		matrix( size_t rows, size_t columns );

		virtual ~matrix();

		size_t rows() const;
		size_t columns() const;
		vector& operator[]( size_t pos );
		vector columnVector( size_t col );
	};

	double dotproduct(const vector& v1, const vector& v2) {
		assert(v1.size() == v2.size());
		double ret = 0.0;
		for (int i = 0; i < v1.size(); i++) {
			ret += v1.at(i) * v2.at(i);
		}
		return ret;
	}

	void mult(matrix& mat1, matrix& mat2, matrix& container) {

		assert(mat1.columns() == mat2.rows());
		assert(container.rows() == mat1.rows());
		assert(container.columns() == mat2.columns());

		for (int rowI = 0; rowI < container.rows(); rowI++) {
			for (int colI = 0; colI < container[rowI].size(); colI++) {
				container[rowI][colI] = dotproduct(mat1[rowI], mat2.columnVector(colI));
			}
		}
	}

	void mult(matrix& mat, vector& vec, vector& container) {
		
		assert(mat.columns() == vec.size());
		assert(container.size() == mat.rows());

		for (int i = 0; i < container.size(); i++) {
			container[i] = dotproduct(mat[i], vec);
		}
	}

	void mult(vector& vec1, vector& vec2, vector& container) {

		assert(vec1.size() == vec2.size());
		assert(container.size() == vec2.size());

		for (int i = 0; i < container.size(); i++) {
			container[i] = vec1[i] * vec2[i];
		}
	}

	void add(vector& vec1, vector& vec2, vector& container) {

		assert(vec1.size() == vec2.size());
		assert(container.size() == vec2.size());

		for (int i = 0; i < container.size(); i++) {
			container[i] = vec1[i] + vec2[i];
		}
	}

}







#endif