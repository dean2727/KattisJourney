#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int t, l, n, i;
    cin >> t;
    while(t--) {
        vector<int> ants;
        int ant;
        cin >> l >> n;
        for (i=0;i<n;i++) {
            cin >> ant;
            ants.push_back(ant);
        }

        sort(ants.begin(), ants.end());
        vector<int> mins;
        for (i=0;i<n;i++) {
            //cout << ants[i] << ", " << l-ants[i] << endl;
            mins.push_back(min(ants[i], l-ants[i]));
        }
        int minTime = mins[0];
        for (i=1;i<n;i++) {
            if (mins[i] > minTime) {
                minTime = mins[i];
            }
        }
        cout << minTime << " " << max(l-ants[0], ants[ants.size()-1]) << "\n";
    }
}