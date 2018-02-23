#include <string>
#include <queue>
#include <iostream>

using namespace std;

class Coord
{
    public:
        Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
        int r() const { return m_r; }
        int c() const { return m_c; }
    private:
        int m_r;
        int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec){
    
    queue<Coord> cQueue;
    Coord current(sr, sc);
    cQueue.push(current);

    char visited = '%';
    maze[sr][sc] = visited;
    int r, c;

    int count = 0;

    while ( ! cQueue.empty()){
        current = cQueue.front();
        r = current.r();
        c = current.c();

        count++;
        cerr << count << ": (" << r << ", " << c << ")" << endl; 

        cQueue.pop();

        if (r == er && c == ec)
            return true;
        
        if (c + 1 < nCols && maze[r][c+1] == '.'){
            cQueue.push(Coord(r, c+1));
            maze[r][c+1] = visited;
        }

        if (r + 1 < nRows && maze[r+1][c] == '.'){
            cQueue.push(Coord(r+1, c));
            maze[r+1][c] = visited;

        }

        if (c - 1 >= 0 && maze[r][c-1] == '.'){
            cQueue.push(Coord(r, c-1));
            maze[r][c-1] = visited;

        }

        if (r - 1 >= 0 && maze[r-1][c] == '.'){
            cQueue.push(Coord(r-1, c));
            maze[r-1][c] = visited;

        }
/*
        cerr << "----------------" << endl;
        for (int i = 0; i < nRows; i++)
            cerr << maze[i] << endl;
        cerr << "----------------" << endl;
  */       

    }

    return false;
}

int main(){
    string mose[10] = {
    "XXXXXXXXXX",
    "X...X..X.X",
    "X..XX....X",
    "X.X.XXXX.X",
    "XXX......X",
    "X...X.XX.X",
    "X.X.X..X.X",
    "X.XXXX.X.X",
    "X..X...X.X",
    "XXXXXXXXXX"
           };
 
    string maze[10];    
    
   for (int u = 0; u < 10; u++)
      maze[u] = mose[u];





if (pathExists(maze, 10,10, 4,3, 1,8))
                    cout << "Solvable!" << endl;
            else
                                cout << "Out of luck!" << endl;




   for (int u = 0; u < 10; u++)
      maze[u] = mose[u];



/*
    cerr << "=====================================================================" << endl;
int total = 0;
for (int i = 1; i < 9; i++)
    for (int j = 1; j < 9; j++){
        for (int k = 1; k < 9; k++)
            for (int l = 1; l < 9; l++){
                 if (mose[i][j] != 'X' && mose[k][l] != 'X' )
                        if ( pathExists(mose, 10,10, i, j, k, l)){
                            cerr << "Start: " << i << "," << j << " End: " << k << "," << l << " Path Found!" << endl;
                 total++;

                        }else
                            cerr << "Start: " << i << "," << j << " End: " << k << "," << l << " Failed!" << endl;
             
                 for (int p = 0; p < 10; p++)
                     mose[p] = maze[p];
            }
            
            cerr << "Total for starting position (" << i << "," << j << "):  " << total << endl;
            total = 0;; 
        }

*/}
