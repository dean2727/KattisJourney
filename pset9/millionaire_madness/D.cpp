#include <iostream>
#include <vector>
#include <queue>
using namespace std;

#define loop(i, a, b) for (i = (a); i < (b); i++)

int i, j;

struct node {
    int val;
    string status;
};

typedef pair<int, pair<int,int> > pn;

bool cmp(const pn& x, const pn& y) {
    return x.first >= y.first;
}

// get distance from 1 pile to another, if negative, return 0, main program should check if it should go 
// the given direction before calling
int getDistance(node **grid, string direction, int x, int y) {
    if (direction == "right") {
        if (grid[x][y+1].val - grid[x][y].val < 0) {
            return 0;
        }
        else {
            return grid[x][y+1].val - grid[x][y].val;
        }
    }
    
    if (direction == "down") {
        if (grid[x+1][y].val - grid[x][y].val < 0) {
            return 0;
        }
        else {
            return grid[x+1][y].val - grid[x][y].val;
        }
    }

    if (direction == "left") {
        if (grid[x][y-1].val - grid[x][y].val < 0) {
            return 0;
        }
        else {
            return grid[x][y-1].val - grid[x][y].val;
        }
    }

    if (direction == "up") {
        if (grid[x-1][y].val - grid[x][y].val < 0) {
            return 0;
        }
        else {
            return grid[x-1][y].val - grid[x][y].val;
        }
    }
}

int main() {
    int minHeight = 0, height, M, N;
    cin >> M >> N;

    // prims algorithm uses priority queue and sorts by the edge weights, pair = <weight, <x,y>>
    priority_queue<pn, vector<pn>, decltype(&cmp)> edges(cmp);

    node** grid = new node *[M];
    loop(i,0,M) {
        grid[i] = new node[N];
    }

    loop(i,0,M) {
        loop(j,0,N) {
            cin >> height;
            grid[i][j].val = height;
            grid[i][j].status = "out";
        }
    }
    
    // start from top left
    grid[0][0].status = "in";
    int inNodes = 1, x = 0, y = 0;
    node n = grid[x][y];

    int right, down, left, up;
    if (y < N-1) {
        right = getDistance(grid, "right", 0, 0);
        edges.push(make_pair(right, make_pair(0, 1)));
    }
    if (x < M-1) {
        down = getDistance(grid, "down", 0, 0);
        edges.push(make_pair(down, make_pair(1, 0)));
    }

    // while we havent hit the bottom right
    while (x != M-1 || y != N-1) {
        pn e = edges.top();
        n = grid[e.second.first][e.second.second];

        // if its already an "in" edge, toss it
        while (n.status == "in") {
            edges.pop();
            e = edges.top();
            n = grid[e.second.first][e.second.second];
        }

        x = e.second.first;
        y = e.second.second;

        // take the edge, if greater than min max, update min max
        if (e.first > minHeight) {
            minHeight = e.first;
        }

        edges.pop();

        // mark as "in", add edges (be aware of its on the edge of the gridge)
        grid[x][y].status = "in";

        // not on left or right edges
        if (y > 0 && y < N-1) {
            left = getDistance(grid, "left", x, y);
            right = getDistance(grid, "right", x, y);
            edges.push(make_pair(left, make_pair(x, y-1)));
            edges.push(make_pair(right, make_pair(x, y+1)));
        }
        // left edge, can get right?
        else if (y == 0 && y != N-1) {
            right = getDistance(grid, "right", x, y);
            edges.push(make_pair(right, make_pair(x, y+1)));
        }
        // right edge, can get left?
        else if (y != 0 && y == N-1) {
            left = getDistance(grid, "left", x, y);
            edges.push(make_pair(left, make_pair(x, y-1)));
        }

        // not on top or bottom edges
        if (x > 0 && x < M-1) {
            up = getDistance(grid, "up", x, y);
            down = getDistance(grid, "down", x, y);
            edges.push(make_pair(up, make_pair(x-1, y)));
            edges.push(make_pair(down, make_pair(x+1, y)));
        }
        // top edge, can get bottom?
        else if (x == 0 && x != M-1) {
            down = getDistance(grid, "down", x, y);
            edges.push(make_pair(down, make_pair(x+1, y)));
        }
        // bottom edge, can get top?
        else if (x != 0 && x == M-1) {
            up = getDistance(grid, "up", x, y);
            edges.push(make_pair(up, make_pair(x-1, y)));
        }
    }

    cout << minHeight;
}