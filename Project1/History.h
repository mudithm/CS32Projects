#ifndef HISTORY_INCLUDED
#define HISTORY_INCLUDED

#include "globals.h"

class History
	{
	  public:
	    History(int nRows, int nCols);
	    ~History();
	    bool record(int r, int c);
	    void display() const;
	  private:
	  	int m_hist[MAXROWS][MAXCOLS] {{0}};
	  	int m_rows;
	  	int m_cols;
	};



#endif // HISTORY_INCLUDED