#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include "globals.h"


class History
{
	public:
		History(int nRows, int nCols);
		bool record(int r, int c);
		void display() const;
	private:
		int	m_rows;
		int m_cols;
		int m_carrots[MAXROWS][MAXCOLS];

		bool isPosInBounds(int r, int c) const;
};



#endif
