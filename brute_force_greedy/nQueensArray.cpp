#include<iostream>
using namespace std;

#define N 14

bool canplace(bool board[N][N], int r, int c) {
   // Says whether can place queen in row r column c
   for (int i = 1; i<=c;i++) {
      if (board[r][c-i]) return false;
      if (((r-i)>=0) && board[r-i][c-i]) return false;
      if (((r+i)<N) && board[r+i][c-i]) return false;
   }
   return true;
}

int placequeens(bool board[N][N], int c) {
   // c is the column to place a queen in
   // This will return the number of ways to place N queens on board
   if (c==N) return 1;
   int numwaystoplace = 0;
   for (int r = 0; r<N; r++) {
      if (canplace(board,r,c)) {
         board[r][c] = true;
         numwaystoplace += placequeens(board,c+1);
         board[r][c] = false;
      }
   }
   return numwaystoplace;
}

int main() {
   bool board[N][N];

   for(int i=0;i<N;i++) for(int j=0;j<N;j++) board[i][j]=false;
   cout << "There are " << placequeens(board,0) << " ways to place queens on the board of size " << N << endl;
}
