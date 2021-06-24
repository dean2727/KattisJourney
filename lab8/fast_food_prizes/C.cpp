#include <iostream>
#include <map>
#include <vector>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n, m, k, type;
        long long money = 0;
        cin >> n >> m;

        vector<int> pm;  // prize type to cash value
        pm.resize(n+1);

        // prize type to the set of sticker types it needs
        map<int, vector<int> > pst;

        // get sticker info
        for (int i=1;i<=n;i++) {
            //cout << "Sticker " << i << endl; 
            cin >> k;
            //cout << "k = " << k << endl;
            // collect the sticker types to claim the prize
            vector<int> st;
            st.resize(k+1);
            for (int j=1;j<=k;j++) {
                cin >> type;
                //cout << type << endl;
                st[j] = type;
            }
            cin >> money;
            pm[i] = money;
            pst.insert(make_pair(i, st));
        }

        // get stickers collected
        vector<int> coll;
        coll.resize(m+1);
        int s;
        for (int i=1;i<=m;i++) {
            cin >> s;
            coll[i] = s;
        }

        // calculate total money. loop through each prize type
        money = 0;
        for (int i=1;i<=pm.size();i++) {
            int minAmt = 1000000000;
            //cout << "sticker type collection size = " << pst[i].size() << endl;
            for (int j=1;j<pst[i].size();j++) {
                // how many stickers of this type do we have?
                int prize = pst[i][j];
                //cout << prize << endl;
                if (coll[prize] < minAmt) {
                    minAmt = coll[prize];
                }
            }

            if (minAmt != 1000000000)
                money += minAmt * pm[i];
        }

        cout << money << endl;
    }
}