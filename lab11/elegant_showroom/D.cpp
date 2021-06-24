#include <iostream>
#include <deque>
using namespace std;

/*
This is a grid graph problem, where we want to find the smallest number of
cars we need to move to get the starting location car out of the building
(until it reached a 'D' on the left or right walls). When we encounter
a 'D' in the search, push this to the front of the deque so it has 
higher priority
*/

int main() {
    int R, C, i, j, x, y;
    cin >> R >> C;
    char grid[R+1][C+1];
    bool visited[R+1][C+1];

    string line;
    for (i=1;i<=R;i++) {
        cin >> line;
        for (j=1;j<=C;j++) {
            grid[i][j] = line.at(j-1);
            visited[i][j] = false;
        }
    }

    // starting location
    cin >> x >> y;

    // initialize deque with starting point car
    deque<pair<pair<int, int>, int> > d;
    pair<pair<int, int>, int> p;
    d.push_front(make_pair(make_pair(x, y), 1));
    visited[x][y] = true;
    int numToMove;
    while (!d.empty()) {
        p = d.front();
        d.pop_front();
        x = p.first.first;
        y = p.first.second;
        numToMove = p.second;

        // if we are on the sides, this has to be a door, so break
        if (y == 1 || y == C || x == 1 || x == R) {
            cout << numToMove;
            break;
        }

        // only take the adjacent spots that are within bounds and not walls
        // if any of the adjacent spots are a 'D' on left or right walls, terminate
        if (y > 1 && grid[x][y-1] != '#' && !visited[x][y-1]) {
            visited[x][y-1] = true;
            // car cell goes to end of queue (bottom of deque), and door cell goes to top (and then pull from front)
            if (grid[x][y-1] == 'D') {
                d.push_front(make_pair(make_pair(x, y-1), numToMove));
            }
            else {
                d.push_back(make_pair(make_pair(x, y-1), numToMove+1));
            }
        }
        if (y < C && grid[x][y+1] != '#' && !visited[x][y+1]) {
            visited[x][y+1] = true;
            // car cell goes to end of queue (bottom of deque), and door cell goes to top (and then pull from front)
            if (grid[x][y+1] == 'D') {
                d.push_front(make_pair(make_pair(x, y+1), numToMove));
            }
            else {
                d.push_back(make_pair(make_pair(x, y+1), numToMove+1));
            }
        }
        if (x > 1 && grid[x-1][y] != '#' && !visited[x-1][y]) {
            if (grid[x-1][y] == 'D') {
                d.push_front(make_pair(make_pair(x-1, y), numToMove));
            }
            else {
                d.push_back(make_pair(make_pair(x-1, y), numToMove+1));
            }
            visited[x-1][y] = true;
        }
        if (x < R && grid[x+1][y] != '#' && !visited[x+1][y]) {
            if (grid[x+1][y] == 'D') {
                d.push_front(make_pair(make_pair(x+1, y), numToMove));
            }
            else {
                d.push_back(make_pair(make_pair(x+1, y), numToMove+1));
            }
            visited[x+1][y] = true;
        }
    }
}