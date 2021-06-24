#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int findset(int i, vector<int> &p) {
    stack<int> s;
    while (i+1 != p[i]) {
        s.push(i+1);
        i = p[i]-1;
    }
    while (!s.empty()) {
        p[s.top()] = i;
        s.pop();
    }
    return i;
}

// merge the sets for the REAL parent vector (ep), and update the sum and total elements
void merge(int p, int q, int ppar, int qpar, vector<int> &par, vector<int> &ep, vector<int> &se, vector<int> &te) {
    cout << "parent ppar: " << ppar << endl;
    cout << "parent qpar: " << qpar << endl;

    if (te[ppar] == te[qpar]) {
        ep[qpar] = ppar;
        par[q] = p;

        te[ppar] += 1;
        te[qpar] -= 1;

        se[ppar] += se[qpar];
        se[qpar] -= q;
    }

    // one with less total elements points to one with more
    else if (te[ppar] < te[qpar]) {
        ep[ppar] = qpar;
        par[p] = q;

        te[qpar] += 1;
        te[ppar] -= 1;

        se[qpar] += q;
        se[ppar] -= p;
    }
    else {
        ep[qpar] = ppar;
        par[q] = p;

        te[ppar] += 1;
        te[qpar] -= 1;

        se[ppar] += q;
        se[qpar] -= q;
    }
}

// move p to the set containing q
void moveElem(int p, int q, int ppar, int qpar, vector<int> &par, vector<int> &ep, vector<int> &se, vector<int> &te) {
    // if total elements for set containing p and set containing 1 are equal...not sure with this yet

    // the parent of p is now q
    ep[ppar] = ep[qpar];

    // subtract p from the p parent location of sum vector and decrement in total vector by 1
    se[ppar] -= p;
    te[ppar] -= 1;

    // p points to q
    par[p] = qpar;
    
    // add p to the q parent location of the sum vector and increment in total vector by 1
    se[qpar] += p;
    te[qpar] += 1;
}

int main() {
    int n = 0, m = 0;
    cin >> n >> m;

    // Create an extra “set” for each element – each element starts out pointing to THAT set instead of itself.
    // Notice, these “false elements” will never be moved, so they are fine to use as the base of a set.
    vector<int> parents(n+1);  // nothing changes in this one
    vector<int> extraParents(n+1);
    // Each set should also store total # of elements (not counting false elements) and sum of elements.
    vector<int> totalElems(n+1);  // NOT the height, its rather number of elements the base set parent points to
    vector<int> sumElems(n+1);  // the sum of the elements with a parent

    for (int i=1;i<=n;i++) {
        parents[i] = i;
        extraParents[i] = i;
        sumElems[i] = i;
        totalElems[i] = 1;
    }

    int command = 0, p = 0, q = 0;
    for (int i=0;i<m;i++) {
        cin >> command;
 
        if (command == 3) {
            cin >> p;
            cout << totalElems[extraParents[parents[p]]] << " " << sumElems[extraParents[parents[p]]] << "\n";
        }

        else {
            cin >> p >> q;
            //cout << p << " " << q << endl;

            // Union the sets containing 𝑝 and 𝑞. If 𝑝 and 𝑞 are already in the same set, ignore this command.
            if (command == 1) {
                merge(p, q, extraParents[parents[p]], extraParents[parents[q]], parents, extraParents, sumElems, totalElems);
            }
            // move p to the set containing q
            else {
                cout << "moving elem\n";
                moveElem(p, q, extraParents[parents[p]], extraParents[parents[q]], parents, extraParents, sumElems, totalElems);
            }
            cout << "debug, lets see all the vectors now:\n";
            cout << "parents:\n";
            for (int i=1;i<=parents.size();i++) {
                cout << parents[i] << " ";
            }
            cout << "\nextra parents:\n";
            for (int i=1;i<=extraParents.size();i++) {
                cout << extraParents[i] << " ";
            }
            cout << "\nsum elem:\n";
            for (int i=1;i<=sumElems.size();i++) {
                cout << sumElems[i] << " ";
            }
            cout << "\ntotal elem:\n";
            for (int i=1;i<=totalElems.size();i++) {
                cout << totalElems[i] << " ";
            }
            cout << "\n\n";
        }

        // for (int j=0;j<parent.size();j++) {
        //     cout << "DEBUG: Element " << j+1 << " has parent " << parent[j] << " and height " << maxheight[j] << endl;
        // }
    }

}
