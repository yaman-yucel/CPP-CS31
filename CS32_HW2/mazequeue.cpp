#include <string>
#include <iostream>
#include <queue>
using namespace std;

class Coord
{
public:
    Coord(int r, int c) : m_row(r), m_col(c) {}
    int r() const { return m_row; }
    int c() const { return m_col; }
private:
    int m_row;
    int m_col;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec);
void printMaze(string maze[], int nRows, int nCols);
bool inBounds(int r, int c, int nRows, int nCols);

//int main()
//{
//    string maze[10] = {
//        "XXXXXXXXXX",
//        "X..X...X.X",
//        "X.XXXX.X.X",
//        "X.X.X..X.X",
//        "X...X.XX.X",
//        "XXX......X",
//        "X.X.XXXX.X",
//        "X.XXX....X",
//        "X...X..X.X",
//        "XXXXXXXXXX"
//    };
//
//    if (pathExists(maze, 10, 10, 5, 3, 8, 8))
//        cout << "Solvable!" << endl;
//    else
//        cout << "Out of luck!" << endl;
//}

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec) {

    //you do not need to check nRows,nCols

    queue<Coord> coordQueue;

    coordQueue.push(Coord(sr, sc)); // push starting point to stack // do not need to check sr sc position

    maze[sr][sc] = 'E'; // mark as encountered

    int count = 0;

    bool debug = false;
    while (!coordQueue.empty()) // while stack is not empty
    {

        Coord topCoord = coordQueue.front(); // save the first item
        coordQueue.pop(); // pop the first item

        if (count < 12 && debug)
        {
            count++;
            cerr << "Coord " << count << ": (" << topCoord.r() << ", " << topCoord.c() << ")" << endl;
            printMaze(maze, nRows, nCols);
        }

        if (topCoord.r() == er && topCoord.c() == ec) // if the point is end point return true
        {
            return true;
        }

        // Check EAST
        if (inBounds(topCoord.r(), topCoord.c() + 1, nRows, nCols))
        {
            if (maze[topCoord.r()][topCoord.c() + 1] == '.')
            {
                coordQueue.push(Coord(topCoord.r(), topCoord.c() + 1)); // push the coordinate
                maze[topCoord.r()][topCoord.c() + 1] = 'E'; // update maze
            }
        }
        // Check NORTH
        if (inBounds(topCoord.r() - 1, topCoord.c(), nRows, nCols))
        {
            if (maze[topCoord.r() - 1][topCoord.c()] == '.')
            {
                coordQueue.push(Coord(topCoord.r() - 1, topCoord.c())); // push the coordinate
                maze[topCoord.r() - 1][topCoord.c()] = 'E'; // update maze
            }
        }

        // Check WEST
        if (inBounds(topCoord.r(), topCoord.c() - 1, nRows, nCols))
        {
            if (maze[topCoord.r()][topCoord.c() - 1] == '.')
            {
                coordQueue.push(Coord(topCoord.r(), topCoord.c() - 1)); // push the coordinate
                maze[topCoord.r()][topCoord.c() - 1] = 'E'; // update maze
            }
        }

        // Check SOUTH movable and not encountered
        if (inBounds(topCoord.r() + 1, topCoord.c(), nRows, nCols))
        {
            if (maze[topCoord.r() + 1][topCoord.c()] == '.')
            {
                coordQueue.push(Coord(topCoord.r() + 1, topCoord.c())); // push the coordinate 
                maze[topCoord.r() + 1][topCoord.c()] = 'E'; // update maze
            }
        }
    }
    return false; // no solution return false

}

bool inBounds(int r, int c, int nRows, int nCols)
{
    if (r >= 0 && r < nRows && c >= 0 && c < nCols)
        return true;
    return false;
}


void printMaze(string maze[], int nRows, int nCols)
{
    for (int i = 0; i < nRows; i++)
    {
        for (int j = 0; j < nCols; j++)
        {
            cerr << maze[i][j];
        }
        cerr << endl;
    }
    cerr << endl;
}