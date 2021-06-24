/*
Disjoint sets:
- Separate sets, all with unique elements, that you can call union
and find on
- each set is identified by the base parent, which points to itself
- max height: the maximum depth height that a set gets to
- 4 arrays:
1. the index of the parents
2. the elements of all the sets
3. the parents of the elements
4. the max height for the set the element is in
(parent array and max height would be global variables)
*/

#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;


/*
Find operation:
- traverse to parent recursively until we find "base"
- update everything along path to point directly to base (this is called path compression)
- in path compression, the tree is getting flatter and flatter, so the actual max height 
of the tree being smaller allows for quicker find operation
- path compression gives much efficiency, you wanna do it
- find is good for telling if there is a connection between 2
elements, avoids extra computation
*/
int findset_recursive(int i, vector<int> &p) {
    if (i == p[i]) return i;

    // with path compression
    p[i] = findset(p[i], p);
    return p[i];

    // without it it would be:
    // return findset(p[i], p);
}

// with really large problems, theres a stack overflow, so do this: fill a stack then empty it
int findset(int i, vector<int> &p) {
    stack<int> s;
    
    // navigate down to the root parent, pushing to the stack
    while (i != p[i]) {
        s.push(i);
        i = p[i];
    }

    // set parent for all visited nodes to the root parent, and return this parent
    while (!s.empty()) {
        p[s.top()] = i;
        s.pop();
    }
    return i;
}

/*
Union operation:
- the idea is to combine 2 disjoint sets together
- first, find the set that each element is in (find the parent)
- case 1: let |A| be max height for set A, and |B| the max height for 
set B. if |A| > |B|, then if using union-by-rank, you would make
B point to A
- case 2: |A| = |B|: pick one at random, and update max height by 1 for
the one being pointed to
- case 3: the 2 elements are in the same set: do nothing
*/
void merge(int x, int y, vector<int> &p, vector<int> &mh) {
    // first, find the set that each element is in (find the parent)
    x = findset(x, p);
    y = findset(y, p);

    // case 2
    if (mh[x] == mh[y]) {
        p[y] = x;
        mh[x]++;  // common height + 1 because we point to the base
    }

    // case 1 (shorter points to longer)
    else if (mh[x] < mh[y]) {
        p[x] = y;  // parent of shorter is the longer
    }
    else {
        p[y] = x;
    }
}


/*
Disjoint sets:
- Separate sets, all with unique elements, that you can call union
and find on
- each set is identified by the base parent, which points to itself
- max height: the maximum depth height that a set gets to
- 4 arrays:
1. the index of the parents
2. the elements of all the sets
3. the parents of the elements
4. the max height for the set the element is in
*/
int main() {
    int n, i, j;
    cin >> n;  // number of sets
    vector<int> parent(n);
    vector<int> maxheight(n);

    for (i=0;i<n;i++) {
        parent.at(i) = i;
        maxheight.at(i) = 1;
    }

    string s;
    cin >> s;
    while (s!="stop") {
        if (s=="list") {
            cout << "The sets are: ";
            for (i=0;i<n;i++) {
                if (parent[i] == i) cout << i << " " << endl;
            }
        }

        else if (s == "find") {
            cin >> i;
            cout << i << " is in set " << findset(i, parent) << endl;
        }

        else if (s == "merge") {
            cin >> i >> j;
            cout << "Merging " << i << " and " << j << endl;
            merge(i, j, parent, maxheight);
        }

        cin >> s;
    }
}

