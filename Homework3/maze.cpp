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

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec)
        return true;
    maze[sr][sc] = 'V';
    // Check north
    if (maze[sr-1][sc] == '.')
        if(pathExists(maze, nRows, nCols, sr-1, sc, er, ec))
            return true;
    // Check west
    if (maze[sr][sc-1] == '.')
        if (pathExists(maze, nRows, nCols, sr, sc-1, er, ec))
            return true;
    // Check south
    if (maze[sr+1][sc] == '.')
        if (pathExists(maze, nRows, nCols, sr+1, sc, er, ec))
            return true;
    // Check east
    if (maze[sr][sc+1] == '.')
        if ( pathExists(maze, nRows, nCols, sr, sc+1, er, ec))
            return true;

    return false;
        
}
