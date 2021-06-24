#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

#define loop(i, a, b) for(i = (a); i < (b); i++)
int i, timer, n;

struct node {
    int color;
    vector<int> adj;
};

vector<node> nodes;
vector<int> start;
vector<int> end_;
vector<int> flatTree;

// fenwick tree representations of all 100 colors
vector<vector<int> > colorCounts(101);

inline int LSOne(const int x) {
    return x & (-x);
}

void incr(int elem, int val, int color) {
    while (elem <= n) {
        colorCounts[color][elem] += val;
        elem = elem + LSOne(elem);
    }
}

int rsq(int elem, int color) {
    int summation = 0;
    vector<int> cc = colorCounts[color];
    while (elem > 0)
    {
        //cout << "elem in rsq = " << elem << endl;
        summation += cc[elem];
        elem -= LSOne(elem);
    }
    return summation;
}

int magicColors(int i, int j) {
    int total = 0;
    //cout << "magic colors, i = " << i << ", j = " << j << endl;

    // loop through each color, see how many in the subtree (of the flattened tree) are of odd count
    int numThisColoredLights;
    for (int c = 1; c <= 100; c++) {
        //cout << "\ncolor: " << c << endl;
        numThisColoredLights = rsq(j-1, c) - rsq(i, c);
        //cout << numThisColoredLights << endl;
        if (numThisColoredLights % 2 == 1) total++;
    }
    
    return total;
}

// DFS traversal of tree with timer and tree flattening
void dfs(int node, int par) {
    start[node] = timer;
    //cout << "node " << node << " encountered at time " << timer << endl;
    flatTree[timer] = node;
    incr(timer, 1, nodes[node].color);
    timer++;

    vector<int> adj = nodes[node].adj;
    for (i=0;i<adj.size();i++) {
        if (adj[i] != par) {
            dfs(adj[i], node);
        }
    }

    end_[node] = timer;
    //cout << "node " << node << " left at time " << timer << endl;
    flatTree[timer] = node;
    //incr(timer, 1, nodes[node].color);
    timer++;
}

void printColorFTs() {
    int j;
    // for (int c = 1; c <= 100; c++) {
    //     cout << "FT for color " << c << ":\n";
    //     //cout << colorCounts[c].size();
    //     vector<int> cc = colorCounts[c];
    //     loop(j, 0, cc.size()) {
    //         cout << cc[j] << " ";
    //     }
    //     cout << endl;
    // }

    vector<int> cc = colorCounts[1];
    for (j = 0; j < cc.size(); j++) {
        cout << j << endl;
        cout << cc[j] << " ";
    }
    cout << endl;
}

/*
This problem has to do with perorming a search
of the tree starting at node X (when query starts with a 0). We keep
a count (starting with 1, since we include the root) for each of the
different colors we see during the search, incrementing in a map.
Then, we can traverse the map and count up how many magic colors
there are (how many were seen an odd number of times)
*/

int main() {
    int N, Q, X, K, C, P, amt;

    cin >> N >> Q;

    // N nodes, N-1 edges
    nodes.resize(N+1);
    start.resize(N+1);
    end_.resize(N+1);
    n = 2*N+1;
    flatTree.resize(n);
    

    // get colors of nodes
    loop(i, 1, N+1) {
        scanf("%d", &C);
        nodes[i].color = C;
    }

    // get parents of nodes (P_i+1 is parent of node i+1)
    loop(i, 2, N+1) {
        scanf("%d", &P);
        nodes[i].adj.push_back(P);
        nodes[P].adj.push_back(i);
    }

    // initialize each of the 100 color vectors
    loop(i, 1, 101) {
        colorCounts[i].resize(n, 0);
    }

    // process the flattened tree using a timer
    // 3 arrays: start, end, and flat tree (size = 2N)
    timer = 1;
    dfs(1, -1);

    // testing
    printColorFTs();
    // cin >> K >> X;
    // cout << magicColors(start[X], end_[X]) << endl;


    loop(i, 0, Q) {
        scanf("%d %d", &K, &X);

        // how many magical colors starting at root X?
        if (K == 0) {
            // we can find the subarray in the flattened tree by querying start and end arrays
            // call ranged sum on the L and R of this subarray
            amt = magicColors(start[X], end_[X]);
            printf("%d\n", amt);
        }
        
        // recolor node X to be color K
        else {
            cin >> K >> X;
            nodes[X].color = K;
            // decrement original color ft
            incr(start[X], -1, nodes[X].color);
            incr(end_[X], -1, nodes[X].color);

            // increment new one
            incr(start[X], 1, K);
            incr(end_[X], 1, K);
        }
    }
}