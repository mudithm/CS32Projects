#include "History.h"

using namespace std;

History::History(int nRows, int nCols){
	m_rows = nRows;
	m_cols = nCols;
}

History::~History(){

}

bool History::record(int r, int c){

	if (r > m_rows || c > m_cols)
		return false;
	else{
		m_hist[r-1][c-1]++;
	}

	return true;

}

void History::display() const{
	
	clearScreen();
    
    for (int r = 1; r <= m_rows; r++)
    {
        for (int c = 1; c <= m_cols; c++)
            if (m_hist[r-1][c-1] >= 26)
            	cout << 'Z';
            else if (m_hist[r-1][c-1] != 0)
            	cout << (char)('A' + m_hist[r-1][c-1] - 1);
            else
            	cout << '.';
        cout << endl;
    }
    cout << endl;

}