#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int N, K, x, t;
    cin >> N >> K;
    vector<pair<int,int> > neg;
    vector<pair<int,int> > pos;
    int delPos = 0, delNeg = 0;
    for (int i=0;i<N;i++) {
        cin>>x>>t;
        if (x < 0) {
            neg.push_back(make_pair(x,t));
            delNeg += t;
        }
        else {
            pos.push_back(make_pair(x,t));
            delPos += t;
        }
    }

    sort(neg.begin(),neg.end());
    sort(pos.begin(),pos.end());

    int totDist = 0;
    int currPos = pos.size()-1;
    int toDel = pos[currPos].second;
    while (delPos > 0) {
        delPos -= K;
        toDel -= K;
        if (toDel < 0) {
            currPos--;
            toDel = pos[currPos].second;
            while (pos[currPos].second )
        }
    }
}