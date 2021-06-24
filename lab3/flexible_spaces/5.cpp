#include <iostream>
#include <set>
#include <vector>
#include <cmath>
using namespace std;

int main() {
    // input
    int W = 0, P = 0, L = 0;
    cin >> W >> P;
    set<int> widths;
    vector<int> segs;
    vector<int> segsRight;
    vector<int> distances;

    for (int i=0;i<P;i++) {
        cin >> L;

        // distances from left wall
        widths.insert(L);
        segs.push_back(L);

    }

    // distances from right wall
    for (int i=0;i<segs.size();i++) {
        segsRight.push_back(W - segs[i]);
    }

    for (int i=0;i<segs.size() - 1;i++) {
        // distances between each other
        int dist = 0;
        for (int j=i+1;j<segs.size();j++) {
            dist = segs[j] - segs[i];
            if (dist != 0) {
                distances.push_back(dist);
            }
        }
    }

    // insert right wall distances
    for (int i=0;i<segsRight.size();i++) {
        widths.insert(segsRight[i]);
    }

    for (int i=0;i<distances.size();i++) {
        widths.insert(distances[i]);
    }

    widths.insert(W);
    

    // output
    set<int>::iterator it=widths.begin();
    cout << *it;
    advance(it, 1);
    bool atEnd = false;
    if (it == widths.end()) {
        atEnd = true;
    }
    while (!atEnd) {
        cout << " " << *it;
        advance(it, 1);
        if (it == widths.end()) {
            atEnd = true;
        }
    }
}