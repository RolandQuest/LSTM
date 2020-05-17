#include "matrix.h"

namespace lstm
{

	matrix::matrix( size_t rows, size_t columns ) {
		_rows = rows;
		_columns = columns;
		_data = ( vector* ) operator new[]( sizeof( vector )* rows );
		for ( int i = 0; i < rows; i++ ) {
			new ( _data + i ) vector( columns );
		}
	}

	matrix::~matrix() {
		delete[] _data;
	}

	size_t matrix::rows() const {
		return _rows;
	}
	size_t matrix::columns() const {
		return _columns;
	}
	vector& matrix::operator[]( size_t pos ) {
		assert( pos < _rows );
		return _data[pos];
	}
	vector matrix::columnVector( size_t col ) {
		assert( col < _columns );
		vector ret( _rows );
		for ( int i = 0; i < _rows; i++ ) {
			ret[i] = _data[i][col];
		}
		return ret;
	}
}
