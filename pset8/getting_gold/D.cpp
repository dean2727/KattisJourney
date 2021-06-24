#include <iostream>
#include <queue>
using namespace std;

#define loop(i, a, b) for(i = (a); i < (b); i++)
int i, j;

/*
This is a grid graph problem, where we want to find the maximum path
from starting point P until we sense a T in a surrounding square
(not diagonally). Path "length" is the number of G's we encounter
on the path
*/

int main() {
    int W, H, maxG = 0;
    int x, y;
    cin >> W >> H;

    char grid[H][W];
    bool visited[H][W];
    string line;
    loop (i, 0, H) {
        cin >> line;
        loop (j, 0, W) {
            grid[i][j] = line.at(j);
            visited[i][j] = false;
            if (line.at(j) == 'P') {
                x = i;
                y = j;
            }
        }
    }

    // using DFS (a stack) to traverse the grid
    queue<pair<int, int> > q;
    pair<int, int> p;
    q.push(make_pair(x, y));

    while (!q.empty()) {
        p = q.front();
        q.pop();
        x = p.first;
        y = p.second;

        // queue up the adjacent squares for this square only if none of the squares have a trap
        if (grid[x-1][y] != 'T' && grid[x+1][y] != 'T' && grid[x][y-1] != 'T' && grid[x][y+1] != 'T') {
            // for adjacent squares, only queue it if its not a wall and hasnt been visited
            // left
            if (grid[x - 1][y] != '#' && !visited[x - 1][y])
            {
                visited[x - 1][y] = true;
                if (grid[x - 1][y] == 'G')
                {
                    maxG++;
                }
                q.push(make_pair(x - 1, y));
            }
            // up
            if (grid[x][y + 1] != '#' && !visited[x][y + 1])
            {
                visited[x][y + 1] = true;
                if (grid[x][y + 1] == 'G')
                {
                    maxG++;
                }
                q.push(make_pair(x, y + 1));
            }
            // right
            if (grid[x + 1][y] != '#' && !visited[x + 1][y])
            {
                visited[x + 1][y] = true;
                if (grid[x + 1][y] == 'G')
                {
                    maxG++;
                }
                q.push(make_pair(x + 1, y));
            }
            // down
            if (grid[x][y - 1] != '#' && !visited[x][y - 1])
            {
                visited[x][y - 1] = true;
                if (grid[x][y - 1] == 'G')
                {
                    maxG++;
                }
                q.push(make_pair(x, y - 1));
            }
        }
        
    }

    cout << maxG;
}