#include <iostream>
#include <vector>
using namespace std;

pair<int,int> nextSpot(char dir, int x, int y) {
    if (dir=='W') {
        return make_pair(x,y-1);
    }
    if (dir=='E') {
        return make_pair(x,y+1);
    }
    if (dir=='S') {
        return make_pair(x+1,y);
    }
    if (dir=='N') {
        return make_pair(x-1,y);
    }
}

int main() {
    int R,C,i,j;
    cin >> R >> C;
    vector<vector<char> > board(R);
    vector<vector<bool> > visited(R);
    for (i=0;i<R;i++) {
        board[i].resize(C);
        visited[i].resize(C);
    }
    for (i=0;i<R;i++) {
        for (j=0;j<C;j++) {
            visited[i][j] = false;
        }
    }

    string row;
    for (i=0;i<R;i++) {
        cin >> row;
        for (j=0;j<row.length();j++) {
            board[i][j] = row[j];
        }
    }

    // follow the direction from position 0,0
    char direction = board[0][0];
    if (direction == 'T') {
        cout << "0";
        return 0;
    }
    int x=0,y=0;
    int numMoves = 0;
    pair<int,int> next = nextSpot(direction, x, y);
    //cout << "NEXT: " << next.first << ", " << next.second << endl;
    numMoves++;
    while (next.first >= 0 && next.first <= R-1 && next.second >= 0 && next.second <= C-1) {
        //cout << "in\n";
        if (board[next.first][next.second] == 'T') {
            cout << numMoves;
            return 0;
        }
        if (visited[next.first][next.second] == true) {
            cout << "Lost";
            return 0;
        }
        visited[next.first][next.second] = true;
        direction = board[next.first][next.second];
        //cout << "next dir is " << direction << endl;
        next = nextSpot(direction, next.first, next.second);
        //cout << "NEXT: " << next.first << ", " << next.second << endl;
        numMoves++;
    }
    cout << "Out";
}