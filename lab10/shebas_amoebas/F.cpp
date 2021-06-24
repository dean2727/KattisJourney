#include <iostream>
#include <vector>
#include <stack>
#include <set>
#include <string>
using namespace std;

#define loop(i,a,b) for(i=a;i<b;i++)

int findset(int i, vector<int> &p) {
    stack<int> s;
    
    // navigate down to the root parent, pushing to the stack
    while (i != p[i]) {
        s.push(i);
        i = p[i];
    }

    // set parent for all visited nodes to the root parent, and return this parent
    while (!s.empty()) {
        p[s.top()] = i;
        s.pop();
    }
    return i;
}

void merge(int x, int y, vector<int> &p, vector<int> &mh) {
    // first, find the set that each element is in (find the parent)
    x = findset(x, p);
    y = findset(y, p);
    //cout << "merging " << x << " and " << y << "\n";
    // case 2
    if (mh[x] == mh[y]) {
        p[y] = x;
        mh[x]++;  // common height + 1 because we point to the base
    }

    // case 1 (shorter points to longer)
    else if (mh[x] < mh[y]) {
        p[x] = y;  // parent of shorter is the longer
    }
    else {
        p[y] = x;
    }
}

int main() {
    int m, n, i, j;
    cin >> m >> n;

    char grid[m][n];
    vector<int> parents;
    vector<int> heights;
    loop(i,0,n*m) {
        parents.push_back(i);
        //cout << i << ": " << parents[i] << endl;
        heights.push_back(1);
    }

    char c;
    loop(i,0,m) {
        loop(j,0,n) {
            cin >> c;
            //cout << c << endl;
            grid[i][j] = c;
        }
    }

    // merge adj marked cells
    loop(i,0,m) {
        loop(j,0,n) {
            // check the 3 adjacent cells from above row and the cell to the left
            if (j >= 1) {
                if (grid[i][j] == '#' && grid[i][j-1] == '#') {
                    // For element [i][j], it is just cell i*m+j
                    merge(i*n+j, i*n+j-1, parents, heights);
                }
            }
            if (i >= 1) {
                if (grid[i][j] == '#' && grid[i-1][j] == '#') {
                    merge(i*n+j, (i-1)*n+j, parents, heights);
                }
                if (j >= 1) {
                    if (grid[i][j] == '#' && grid[i-1][j-1] == '#') {
                        merge(i*n+j, (i-1)*n+j-1, parents, heights);
                    }
                }
                if (j < n-1) {
                    if (grid[i][j] == '#' && grid[i-1][j+1] == '#') {
                        merge(i*n+j, (i-1)*n+j+1, parents, heights);
                    }
                }
            }
        }
    }

    set<int> count;
    loop(i,0,heights.size()) {
        //cout << i << ": " << parents[i] << endl;
        int row = i / n;
        int col = i % n;
        if (grid[row][col] == '#') {
            count.insert(findset(i, parents));
        }
    }
    // for (set<int>::iterator it=count.begin();it!=count.end();it++) {
    //     cout << *it << endl;
    // }
    if (count.empty()) cout << "0";
    else cout << count.size();
}