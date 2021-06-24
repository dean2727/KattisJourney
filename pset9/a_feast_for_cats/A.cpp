#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

#define loop(i, a, b) for (i = (a); i < (b); i++)
#define trav(a, x) for (auto &a : x)

/*
This problem uses prims algorithm to find minimum spanning tree of
the graph formed for where the cats are and their distances from each other. Using
prims because we start at vertex 0 (the fridge). Algorithm greedily pulls out smallest
edges to "out" nodes
*/

struct node {
    int val;
    vector<int> adj;
    vector<int> dist;
    string status;
}; 

typedef pair<int, int> pn;

bool cmp(const pn& x, const pn& y) {
    return x.first >= y.first;
}

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int m, c, d, i, j, lines, x;
        node n;

        // m millileters of milk, c cats
        cin >> m >> c;

        vector<node> cats(c);
        loop(i, 0, c) {
            cats[i].val = i;
            cats[i].status = "out";
        }

        lines = (c * (c - 1)) / 2;
        loop(x, 0, lines) {
            cin >> i >> j >> d;
            cats[i].adj.push_back(j);
            cats[i].dist.push_back(d);
            cats[j].adj.push_back(i);
            cats[j].dist.push_back(d);
        }

        int amtMilk = 1;
        cats[0].status = "in";
        int inNodes = 1;

        // prims algorithm uses priority queue and sorts by the edge weights
        priority_queue<pn, vector<pn>, decltype(&cmp)> edges(cmp);

        // initialize with first innode, push all adjacent edges to the fridge
        n = cats[0];
        loop(i, 0, n.adj.size()) {
            edges.push(make_pair(n.dist[i], n.adj[i]));
        }
        bool cant = false;
        
        // want every node (cat) to be an "in" node
        while (inNodes != c) {
            // pull out next smallest edge
            pn e = edges.top();
            n = cats[e.second];

            // if its already an "in" edge, toss it
            while (n.status == "in") {
                edges.pop();
                e = edges.top();
                n = cats[e.second];
            }

            // add edge weight to the amount of milk used (spill 1 ml per meter) as well as 1 ml to feed the cat
            amtMilk += e.first + 1;

            // if milk amount surpassed the amount of milk in the fridge, cant reach all cats
            if (amtMilk > m) {
                cout << "no\n";
                cant = true;
                break;
            }

            edges.pop();

            // mark the cat as an "in" cat
            cats[n.val].status = "in";
            inNodes++;

            // add its edges to the priority queue
            loop(i, 0, n.adj.size()) {
                edges.push(make_pair(n.dist[i], n.adj[i]));
            }
        }

        if (!cant) cout << "yes\n";
    }
}
