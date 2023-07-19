// uses clearScreen
#include "globals.h"
#include "History.h"

#include <iostream>
#include <string>


History::History(int nRows, int nCols) {
	// Check etme demisler alttakileri
	m_rows = nRows;
	m_cols = nCols;
	for (int r = 1; r <= m_rows; r++)
		for (int c = 1; c <= m_cols; c++)
			m_carrots[r - 1][c - 1] = 0; // Initialize carrot records as 0.
}


bool History::record(int r, int c) {
	
	if (isPosInBounds(r, c))
	{
		//Record what you need to 
		m_carrots[r - 1][c - 1] += 1;

		return true;
	}
	return false;

}

void History::display() const {

	char displayGrid[MAXROWS][MAXCOLS];
	int r, c;

	std::string alphabet = ".ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	// Fill displayGrid with dots (empty) and alphabet letters.
	for (r = 1; r <= m_rows; r++)
		for (c = 1; c <= m_cols; c++)
			if (m_carrots[r - 1][c - 1] > 26)
				displayGrid[r - 1][c - 1] = 'Z';
			else
				displayGrid[r - 1][c - 1] = alphabet[m_carrots[r - 1][c - 1]];

	clearScreen();
	for (r = 1; r <= m_rows; r++)
	{
		for (c = 1; c <= m_cols; c++)
			std::cout << displayGrid[r - 1][c - 1];
		std::cout << std::endl;
	}
	std::cout << std::endl;

}

bool History::isPosInBounds(int r, int c) const
{
	return (r >= 1 && r <= m_rows && c >= 1 && c <= m_cols);
}
