#include <iostream>

#include "lstm.h"
#include "matrix.h"

int main() {


	lstm::lstm_cell cell(5, 5);

	cell.Activate();

	std::cin.get();
	return 0;
}