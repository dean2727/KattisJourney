#include<iostream>

using namespace std;

int N; // Size of the board
bool** board;
bool* rc;
bool* dc1;
bool* dc2;

// Returns whether a location is currently OK to place a queen in
int tryplace(int r, int c) {
   // Check if a queen is already in this row
   if (rc[r]) return 0;
   // Check if a queen is already in this upward diagonal
   if (dc1[r+c]) return 0;
   // Check if a queen is already in this downward diagonal
   if (dc2[N-r+c-1]) return 0;
   // Since no queen on this row or either diagonal, it's OK to place here
   return 1;
}

inline void placequeen(int r, int c) {
   // Mark the row and both diagonals for this position
   rc[r] = true;
   dc1[r+c]=true;
   dc2[N-r+c-1]=true;
}

inline void removequeen(int r, int c) {
   // Unmark the row and both diagonals for this position
   rc[r] = false;
   dc1[r+c]=false;
   dc2[N-r+c-1]=false;
}

// Returns count of how many options for board in current position
int places(int coltoplace) {
   int numoptions=0;
   int i, j;
   if (coltoplace == N-1) {
      // Last column, so just check each spot; no recursion needed
      // Could also just replace this with check for coltoplace==n and return 1
      for(i=0;i<N;i++) {
         if (tryplace(i,coltoplace)) {numoptions++;}
      }
      return numoptions;
   }
   for (i=0;i<N;i++) {
      // For row i, we will try to place a queen in the current column
      if (tryplace(i,coltoplace)) {
         // It's possible, so we will place the queen, call recursion, and then
         //      remove the queen
         placequeen(i,coltoplace);
         numoptions+=places(coltoplace+1);
         removequeen(i,coltoplace);
      }
   }
   return numoptions;
}

int main() {
   int i, j;
   int r, c;
   // Read in board size
   cin >> N;
   // Note: We do NOT need to actually keep track of the board!  We just
   //       keep track of which rows and diagonals of the board are occuplied
   rc = new bool[N];       // Keep track of whether row occupied
   dc1 = new bool[2*N-1];  // Keep track of whether upward diagonal occupied
   dc2 = new bool[2*N-1];  // Keep track of whether downward diagonal occupied
   for(i=0;i<N;i++) {
      // Initialize board and row/diagonal arrays to false
      rc[i] = false;
      dc1[i]=false; dc1[2*N-i-1] = false;
      dc2[i]=false; dc2[2*N-i-1] = false;
   }
   cout << "For a board of size " << N << " we can place queens " << places(0) << " ways." << endl;

   return 0;
}
