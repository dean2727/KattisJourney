#include <iostream>
#include <vector>
#include <queue>
#include <map>
using namespace std;

typedef map<string, int>::iterator mit;
#define trav(a, x) for(auto& a : x)

// graph is adjacency list since we can have 100,000 vertices
// nodes are the items to buy, edge from u to v means cant buy u with v
struct node {
    string item;
    vector<string> adj;
};

int main() {
    int N;
    cin >> N;

    vector<node> vec(N);
    map<string, int> itemIdx;

    string item;
    for (int i=0;i<N;i++) {
        cin >> item;
        vec[i].item = item;
        itemIdx.insert(make_pair(item, i));
    }

    // get the edges
    int M;
    cin >> M;
    string i1, i2;
    for (int i=0;i<M;i++) {
        cin >> i1 >> i2;
        vec[itemIdx[i1]].adj.push_back(i2);
        vec[itemIdx[i2]].adj.push_back(i1);
    }

    mit it;

    // we want to check if this graph is bipartite, i.e. if we can set node u to a different
    // color from node v for every bad item pairing u, v (2 coloring problem)
    // lets create a mapping of items to colors. color1 = 1, color2 = 0. initially, all have no color (-1)
    map<string, int> colors;
    trav(it, itemIdx) {
        colors.insert(make_pair(it.first, -1));
    }

    // assign first color to the first item
    it = colors.begin();
    while (it != colors.end()) {
        if (colors[it -> first] != -1) {
            advance(it, 1);
            continue;
        }
        colors[it -> first] = 1;

        // use BFS traversal for the coloring
        queue<string> items;
        items.push(it -> first);
        while (!items.empty()) {
            string u = items.front();
            items.pop();

            // find all non-colored adjacent vertices
            vector<string> adj = vec[itemIdx[u]].adj;
            for (int i=0;i<adj.size();i++) {
                string v = adj[i];

                // if both u and v are -1, then we are on a different component, color u 1 and v 0
                if (colors[u] == -1 && colors[v] == -1) {
                    colors[u] = 1;
                    colors[v] = 0;
                    items.push(u);
                    items.push(v);
                }

                // else, if edge exists and v isnt colored, color it the alternative color
                else if (colors[v] == -1) {
                    colors[v] = 1 - colors[u];
                    items.push(v);
                }

                // else, if v is colored the same color, we cant assign the items amongst Jesse and Walter
                else if (colors[u] == colors[v]) {
                    cout << "impossible";
                    return 0;
                }
            }
        }
        advance(it, 1);
    }

    // if we got here, we have colors assigned, so just print out the items for color 0 and for color 1
    it = colors.begin();
    vector<string> c0;
    vector<string> c1;
    trav(it, colors) {
        if (it.second == 0) c0.push_back(it.first);
        else c1.push_back(it.first);
    }

    for (int i=0;i<c1.size();i++) {
        cout << c1[i] << " ";
    }
    cout << "\n";
    for (int i=0;i<c0.size();i++) {
        cout << c0[i] << " ";
    }
}