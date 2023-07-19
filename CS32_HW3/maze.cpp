bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    if (sr == er && sc == ec) // no bounds check needed since there are X's at the walls.
        return true;

    maze[sr][sc] = 'E';

    if (maze[sr + 1][sc] == '.' && pathExists(maze, nRows, nCols, sr + 1, sc , er , ec))
        return true;
    if (maze[sr][sc - 1] == '.' && pathExists(maze, nRows, nCols, sr, sc - 1, er, ec))
        return true;
    if (maze[sr - 1][sc] == '.' && pathExists(maze, nRows, nCols, sr - 1, sc, er, ec))
        return true;
    if (maze[sr][sc + 1] == '.' && pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
        return true;
    return false;
}