#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int n, m, i, j;
    cin >> n;
    for (i=0;i<n;i++) {
        cin >> m;
        int val;
        vector<int> vals;
        for (j=0;j<m;j++) {
            cin >> val;
            vals.push_back(val);
        }

        int prev = vals[1] - vals[0];
        bool perm = true;
        for (j=1;j<m-1;j++) {
            if (vals[j+1] - vals[j] != prev) {
                perm = false;
                break;
            }
        }

        if (!perm) {
            sort(vals.begin(), vals.end());
            prev = vals[1] - vals[0];
            perm = true;
            for (j=1;j<m-1;j++) {
                if (vals[j+1] - vals[j] != prev) {
                    perm = false;
                    break;
                }
            }
            if (!perm) {
                cout << "non-arithmetic\n";
            }
            else {
                cout << "permuted arithmetic\n";
            }
        }
        else {
            cout << "arithmetic\n";
        }
    }
}