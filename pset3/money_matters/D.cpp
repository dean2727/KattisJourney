#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

bool sortbysec(const pair<int,int> &a,
              const pair<int,int> &b)
{
    return (a.second < b.second);
}

int findset(int i, vector<int> &p) {
    stack<int> s;
    while (i != p[i]) {
        s.push(i);
        i = p[i];
    }
    while (!s.empty()) {
        p[s.top()] = i;
        s.pop();
    }
    return i;
}

void merge(int x, int y, vector<int> &p, vector<int> &mh, vector<int> &v) {

    // first, find the set that each element is in (find the parent)
    x = findset(x, p);
    y = findset(y, p);

    int xVal = v[x], yVal = v[y];

    // case 2
    if (mh[x] == mh[y]) {
        if (abs(yVal) < abs(xVal)) {
            p[y] = x;  // y points to x
            mh[x]++;
            v[x] += yVal;
            v[y] -= yVal;
        }
        else {
            p[x] = y;  // x points to y
            mh[y]++;
            v[y] += xVal;
            v[x] -= xVal;
        }
    }

    // case 1 (shorter points to longer)
    else if (mh[x] < mh[y]) {
        p[x] = y;  // parent of shorter is the longer
        v[y] += xVal;
        v[x] -= xVal;
    }
    else {
        p[y] = x;
        v[x] += yVal;
        v[y] -= yVal;
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    vector<int> parent(n);
    vector<int> height(n);
    vector<int> values(n);

    int i = 0, amt = 0;
    while (n--) {
        cin >> amt;
        parent.at(i) = i;
        height.at(i) = 1;
        values.at(i) = amt;
        i++;
    }

    // as we read in pairs, union the 2 people together
    int x, y;
    vector<pair<int, int> > pairs;
    while (m--) {
        cin >> x >> y;
        pairs.push_back(make_pair(x, y));
    }

    sort(pairs.begin(), pairs.end(), sortbysec);

    for (int i=0;i<pairs.size();i++) {
        merge(pairs[i].first, pairs[i].second, parent, height, values);
        // for (int j=0;j<parent.size();j++) {
        //     cout << "pair: " << pairs[i].first << ", " << pairs[i].second << endl;
        //     cout << parent[i] << ":" << height[i] << ":" << values[i] << endl;
        // }
        // cout << endl;
    }

    for (int i=0;i<values.size();i++) {
        if (values[i] != 0) {
            cout << "IMPOSSIBLE";
            return 0;
        }
    }

    cout << "POSSIBLE";
	return 0;
}
