#include <iostream>
#include <string>
#include <map>
#include <iomanip>
using namespace std;

#define endl '\n'
#define trav(a, x) for(auto& a : x)
#define loop(i, a, b) for(i = (a); i < (b); i++)

int N;
vector<int> animalEncl;

// can a species be placed in an enclosure? aka, are 2 or more spots in the row true?
bool cansee(bool enclosures[N+1][N+1], bool species[N+1][N+1], int r, int c) {
    if (enclosures[r][c]) return false;
    if (r < N) {
        
        if (species[r-1] == r || species[r+1]) {
            return false;
        }
        if (r >)
    }
   for (int i = 1; i<=c;i++) {
      if (board[r][c-i]) return false;
      if (((r-i)>=0) && board[r-i][c-i]) return false;
      if (((r+i)<N) && board[r+i][c-i]) return false;
   }
   return true;
}

// place each species in an enclosure
void placespecies(int c, bool enclosures[N+1][N+1], int species[N+1][N+1]) {
   if (c==N) return 1;
   for (int r = 1; r <= N; r++) {
      if (canplace(enclosures, species, r, c)) {
         board[r][c] = true;
         numwaystoplace += placequeens(board,c+1);
         board[r][c] = false;
      }
   }
}

int main() {
    int i, j;
    cin >> N;
    animalEncl.resize(N+1);

    // representing which enclosures can see which via an N x N table
    bool enclosures[N+1][N+1];
    int species[N+1][N+1];
    loop (i, 0, N+1) {
        loop (j, 0, N+1) {
            enclosures[i][j] = false;
            species[i][j] = 0;
        }
    }

    string ep;
    while (cin >> ep){
        int e1 = int(ep[0]) - 48, e2 = int(ep[2]) - 48;
        enclosures[e1][e2] = true;
        enclosures[e2][e1] = true;
    }

    // For every position x, try to place animal 1, then 2, then 3, then 4 on it
    // An animal is not possible if one of the visible enclosures already has that animal type in it – need to check all adjacent ones
    // If you encounter a problem where none of the 4 work, use backtracking to undo to previous step
    placespecies(1, enclosures, species);

    loop (i, 1, N+1) {
        cout << i << " " << animalEncl[i] << endl;
    }
}