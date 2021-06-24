#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <queue>
#include <stack>
using namespace std;

struct node {
    string station;
    vector<int> adj;
    bool visited;
};

void tokenize(string const &str, const char delim, vector<string> &out) {
	size_t start;
	size_t end = 0;
	while ((start = str.find_first_not_of(delim, end)) != string::npos) {
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

int main() {
    int N, i, j;
    char delim = ' ';
    string line;

    cin >> N;
    getline(cin, line);

    map<string, int> s2n;
    set<pair<string, string> > doneEdges;
    int nodeNum = 0;

    // first, we need to figure out the # of distinct stations by inserting into a set (also store input)
    set<string> distinctStations;
    vector<vector<string> > input;
    for (i=0;i<N;i++) {
        getline(cin, line);
        vector<string> toks;
        tokenize(line, delim, toks);
        input.push_back(toks);
        for (j=0;j<toks.size();j++) {
            distinctStations.insert(toks[j]);
        }
    }

    vector<node> stations(distinctStations.size());

    // for a line, first thing is the source, rest are destinations, make undirected unweighted graph
    vector<string> toks;
    for (i=0;i<N;i++) {
        toks = input[i];
        string from = toks[0];

        // if station isnt in node mapping, create the mapping
        if (!s2n.count(from)) {
            s2n[from] = nodeNum;
            node n;
            n.station = from;
            n.visited = false;
            stations[nodeNum] = n;
            nodeNum++;
        }

        string to;
        for (j=1;j<toks.size();j++) {
            to = toks[j];
            if (!s2n.count(to)) {
                s2n[to] = nodeNum;
                node n;
                n.station = to;
                n.visited = false;
                stations[nodeNum] = n;
                nodeNum++;
            }

            // from to to edge could have already been added
            if (!doneEdges.count(make_pair(from, to))) {
                stations[s2n[from]].adj.push_back(s2n[to]);
                doneEdges.insert(make_pair(from, to));
            }

            // to to from edge could have already been added
            if (!doneEdges.count(make_pair(to, from))) {
                stations[s2n[to]].adj.push_back(s2n[from]);
                doneEdges.insert(make_pair(to, from));
            }
        }
    }

    // get starting and ending destination
    string start, end;
    cin >> start >> end;

    // perform a BFS on the stations, keeping track of parent values (node numbers)
    bool noRouteFound = true;
    stations[s2n[start]].visited = true;
    map<int, string> nodeToParent;
    // parent of the start is just empty string
    nodeToParent[s2n[start]] = "";
    queue<node> q;
    q.push(stations[s2n[start]]);
    while (!q.empty()) {
        node fr = q.front();
        string stationName = fr.station;
        q.pop();

        vector<int> adj = stations[s2n[stationName]].adj;
        for (i=0;i<adj.size();i++) {
            if (!stations[adj[i]].visited) {
                nodeToParent[adj[i]] = fr.station;
                // are we at the destionation? if so, terminate
                if (stations[adj[i]].station == end) {
                    noRouteFound = false;
                    break;
                }
                stations[adj[i]].visited = true;
                q.push(stations[adj[i]]);
            }
        }
    }

    // if we coulnt make it to the end destination, print no route found
    if (noRouteFound) cout << "no route found";
    // otherwise, use the parent vector to trace the path from the start to the end
    else {
        stack<string> trace;
        trace.push(end);
        string parent = nodeToParent[s2n[end]];
        while (parent != "") {
            trace.push(parent);
            parent = nodeToParent[s2n[parent]];
        }
        while (!trace.empty()) {
            cout << trace.top() << " ";
            trace.pop();
        }
    }
}