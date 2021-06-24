#include <iostream>
#include <vector>
using namespace std;

//#define N 8
int N;

bool canplace(vector<vector<bool>> &board, int r, int c) {
    // do already have something in the row?
    for (int i=1;i<=c;i++) {
        if (board[r][c-i]) return false;
        // already in diagonal?
        if (((r-i) >= 0) && board[r-i][c-i]) return false;
        if (((r+i) < N) && board[r+i][c-i]) return false;
    }
    return true;
}

int placequeens(vector<vector<bool>> &board, int c) {
    // c is the column to place a queen in
    // returns the number of ways to place N queens on board
    if (c==N) return 1;
    int numWaysToPlace = 0;

    // try to place a queen in every row in this column
    // can also keep check some new arrays of bools that represent if 
    // there are queens in rows or in diagonals. e.g. bool rows[8] for an 8x8 board,
    // and bool diagonals[2*8 - 1] (2N - 1), where the diagonal for a spot [r][c] is index r + c,
    // and then another bool diagonals[15] for the other direction of diagonals
    for (int r=0;r<N;r++) {
        if (canplace(board, r, c)) {
            board[r][c] = true;
            numWaysToPlace += placequeens(board, c+1);
            board[r][c] = false;
        }
    }

    return numWaysToPlace;
}

int main() {
    cin >> N;

    // vectors used because its dynamic and can be formed during runtime
    vector<vector<bool> > board(N);
    vector<bool> row(N, false);
    for (int i=0;i<N;i++) board[i] = row;

    cout << "There are " << placequeens(board, 0) << " ways to place queens on the board of size " << N << "\n";
}