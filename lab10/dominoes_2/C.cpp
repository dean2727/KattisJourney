#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

set<int> seen;
int kot;
vector<vector<int> > doms;

void bfs(int d) {
    queue<int> q;
    q.push(d);

    int cur;
    while (!q.empty()) {
        cur = q.front();
        q.pop();

        int next;
        for (int i=0;i<doms[cur].size();i++) {
            next = doms[cur][i];
            //cout << next << endl;
            if (!seen.count(next)) {
                kot++;
                //cout << kot << endl;
                seen.insert(next);
                q.push(next);
            }
        }
    }
}

int main() {
    int t, n, m, l, i, j;
    cin >> t;
    while(t--){
        cin>>n>>m>>l;
        kot = 0;
        doms.resize(n+1);
        int e1,e2;
        for (i=0;i<m;i++) {
            cin>>e1>>e2;
            doms[e1].push_back(e2);
        }
        
        int ko;
        for (i=0;i<l;i++) {
            cin >> ko;
            if (!seen.count(ko)) kot++;
            seen.insert(ko);
            //cout << kot << endl;

            // do a search for every knocked over domino
            bfs(ko);
        }

        cout << kot << "\n";
        seen.clear();
        doms.clear();
        kot = 0;
    }
}