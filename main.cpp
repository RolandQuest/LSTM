#include <iostream>
#include <time.h>

#include "lstm.h"
#include "matrix.h"
#include "vector.h"


int main() {

	lstm::lstm_cell cell(100, 100);

	clock_t start = clock();

	for ( int i = 0; i < 1000; i++ ) {
		cell.Activate();
	}

	clock_t stop = clock();

	std::cout << ( difftime( stop, start ) ) << '\n';

	//std::cin.get();
	return 0;
}