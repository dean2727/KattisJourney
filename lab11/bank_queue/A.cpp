#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

bool cmp(const pair<int,int>& a, const pair<int,int>& b) {
    return a.first > b.first;
}

int main() {
    int N, T, c, t;
    cin >> N >> T;
    vector<pair<int,int> > vp;
    for (int i=0;i<N;i++) {
        cin >> c >> t;
        vp.push_back(make_pair(c, t));
    }

    // order people by most $ to least $
    sort(vp.begin(), vp.end(), cmp);

    // greedily put most money at the latest time possible for the person with that much money
    vector<int> moneys(T, 0);
    int numAssigned = 0, total = 0;
    for (int i=0;i<vp.size();i++) {
        //cout << vp[i].second << endl;
        int spot = vp[i].second;
        // if this time slot is taken, move down time spot until we can find an open slot
        while (moneys[spot] && spot >= 0) {
            //cout << i << ", " << spot << endl;
            spot--;
        }
        if (spot != -1) {
            moneys[spot] = vp[i].first;
            numAssigned++;
            total += vp[i].first;
            if (numAssigned == T) break;
        }
    }
    cout << total;
}