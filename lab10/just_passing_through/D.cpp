#include <iostream>
#include <map>
#include <vector>
using namespace std;

#define loop(i,a,b) for(i=a;i<b;i++)
#define MAXINT 1000000000

vector<vector<int> > daMap;
vector<vector<bool> > passes;
int numPasses;
int r;

/*
DP[i][j][b]: minimum cost to get to position <i, j> where you have b passes you must cross

Base case:
- if square <i, j> is -1 (undrivable), return MAXINT (cant go there)
- if j = 0, we are on first column. 
    - if b = n, this is what we want, take height of square <i, j>
    - else, return MAXINT

If square <i, j> is a pass
DP[i][j][b] = height of <i, j> + min {
    DP[i-1][j-1][b+1] (going to the northwest),
    DP[i][j-1][b+1] (going to the west),
    DP[i+1][j-1][b+1] (going to the southwest)
}

Else, its not a pass
DP[i][j][b] = height of <i, j> + min {
    DP[i-1][j-1][b] (going to the northwest),
    DP[i][j-1][b] (going to the west),
    DP[i+1][j-1][b] (going to the southwest)
}

For each row, run the DP with j = c - 1 and b = 0, and take the minimum
*/

int minTravel(int i, int j, int b) {
    //cout << b << endl;
    //cout << "column " << j << endl;
    if (i < 0 || j < 0 || i >= r) return MAXINT;
    if (daMap[i][j] == -1) return MAXINT;
    if (j == 0) {
        if (b != numPasses) return MAXINT;
        else {
            //cout << "returning " << daMap[i][j] << " (first column)\n";
            return daMap[i][j];
        }
    }

    int ret = daMap[i][j], min1;
    if (passes[i][j]) {
        //cout << "on a pass at " << i << ", " << j << endl;
        // from NW and W
        min1 = min(minTravel(i-1, j-1, b+1), minTravel(i, j-1, b+1));
        // min of this min and going to SW
        ret += min(min1, minTravel(i+1, j-1, b+1));
    }

    else {
        min1 = min(minTravel(i-1, j-1, b), minTravel(i, j-1, b));
        ret += min(min1, minTravel(i+1, j-1, b));
    }
    //cout << ret << endl;
    return ret;
}

int main() {
    int c,n,i,j,tile;
    cin >> r >> c >> n;

    passes.resize(r);
    daMap.resize(r);
    numPasses = 0;

    loop(i,0,r) {
        daMap[i].resize(c);
        passes[i].resize(c);
    }

    // develop the map
    loop(i,0,r) {
        loop(j,0,c) {
            cin >> tile;
            daMap[i][j] = tile;
            passes[i][j] = false;
        }
    }

    // mark passes (east and west are lower, north and south are higher)
    // restricting loop bounds allows us to circumvent an if check every time for border spots
    loop(i,1,r-1) {
        loop(j,1,c-1) {
            // passes cant be adjacent to (north, south, east, west) undrivable spots
            if (daMap[i-1][j] != -1 && daMap[i][j-1] != -1 && daMap[i+1][j] != -1 && daMap[i][j+1] != -1) {
                int daSpot = daMap[i][j];
                if (daMap[i-1][j] > daSpot && daMap[i+1][j] > daSpot && daMap[i][j-1] < daSpot && daMap[i][j+1] < daSpot) {
                    passes[i][j] = true;
                    numPasses++;
                }
            }
        }
    }

    // if there arent enough passes (< n), impossible
    if (numPasses < n) {
        cout << "impossible";
        return 0;
    }

    int minTrav = MAXINT, thisGo;
    // loop(i,0,r) {
    //     thisGo = minTravel(i, c-1, 0);
    //     cout << thisGo << endl;
    //     if (thisGo < minTrav) {
    //         minTrav = thisGo;
    //     }
    // }
    minTrav = minTravel(1, c-1, 0);

    // all routes blocked by undrivable locations, so impossible
    if (minTrav >= MAXINT) cout << "impossible";
    else cout << minTrav;
}