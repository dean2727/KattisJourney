#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

bool cmp (const int& lhs, const int& rhs) {
   if (rhs < lhs) {
       return true;
   }
   else {
       return false;
   }
}


int main() {
    int N = 0, i, j;
    cin >> N;

    // for each case, get the longest segments for each color,
    // making sure we alternate
    int numSegs = 0, maxLength = 0;
    string segment;
    for (i = 0; i < N; i++) {
        cin >> numSegs;

        vector<char> reds;
        vector<char> blues;

        string seg;
        for (j = 0; j < numSegs; j++) {
            cin >> seg;
            //cout << "Segment: " << seg.back() << endl;
            if (seg.back() == 'R') {
                reds.push_back(stoi(seg));
            }
            else {
                blues.push_back(stoi(seg));
            }
        }

        // output 0 if either vector has no elements
        if (reds.empty() || blues.empty()) {
            cout << "Case #" << i + 1 << ": 0\n";
            continue;
        }

        // sort vectors in reverse order
        sort(reds.begin(), reds.end(), cmp);
        sort(blues.begin(), blues.end(), cmp);

        for (j = 0; j < min(reds.size(), blues.size()); j++) {
            maxLength += reds[j] + blues[j] - 2;
        }
        cout << "Case #" << i + 1 << ": " << maxLength << endl;
        
        maxLength = 0;
    }
}