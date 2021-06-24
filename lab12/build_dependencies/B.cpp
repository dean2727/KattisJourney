#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>
using namespace std;

#define loop(i, a, b) for(i=a;i<b;i++)

void tokenize(string const &str, const char delim,
 vector<string> &out) {
	size_t start;
	size_t end = 0;
	while ((start = str.find_first_not_of(delim, end)) != string::npos) {
		end = str.find(delim, start);
		out.push_back(str.substr(start, end - start));
	}
}

vector<vector<string> > dependencies;
map<string, int> fileToNodeNum;
map<int, string> nodeNumToFile;

vector<string> topologicalSortBFS(int n, string start) { 
    queue<string> q; 
    vector<int> indegree(n, 0);
    vector<string> solution;
    int i, j;

    loop(i, 0, n) {
        loop(j, 0, dependencies[i].size()) {
            indegree[fileToNodeNum[dependencies[i][j]]]++;
        }
    }
    
    // enqueue nodes with indegree 0
    loop(i, 0, n) {
        if (indegree[i] == 0) q.push(nodeNumToFile[i]);
    }

    while (!q.empty()) {
        string currentNode = q.front();
        q.pop();
        solution.push_back(currentNode);

        loop(j, 0, dependencies[fileToNodeNum[currentNode]].size()) {
            // remove all edges
            string newNode = dependencies[fileToNodeNum[currentNode]][j];
            indegree[fileToNodeNum[newNode]]--;

            // target node has now no more incoming edges -> wanna process it next
            if (indegree[fileToNodeNum[newNode]] == 0) { 
                q.push(newNode);
            }
        }
    }

    return solution;
}

int main() {
    int n, i;
    cin >> n;
    string line;
    getline(cin, line);
    dependencies.resize(n);
    const char delim = ' ';
    int nodeNum = 0;

    loop(i, 0, n) {
        getline(cin, line);
        vector<string> parts;
        tokenize(line, delim, parts);

        // draw edges from dependency to file thats changed when dependency changes (first file)
        string fileA = parts[0].substr(0, parts[0].length()-1);  // dont include the colon
        if (!fileToNodeNum.count(fileA)) {
            fileToNodeNum[fileA] = nodeNum;   
            nodeNumToFile[nodeNum] = fileA;         
            nodeNum++;
        }
        string fileB;
        for (int j=1;j<parts.size();j++) {
            fileB = parts[j];
            if (!fileToNodeNum.count(fileB)) {
                fileToNodeNum[fileB] = nodeNum;     
                nodeNumToFile[nodeNum] = fileB;       
                nodeNum++;
            }
            dependencies[fileToNodeNum[fileB]].push_back(fileA);
        }
    }

    string start;
    cin >> start;
    vector<string> soln = topologicalSortBFS(n, start);

    // only consider the nodes reachable from the start node
    set<string> reachable;
    queue<string> q;
    q.push(start);
    while (!q.empty()) {
        string front = q.front();
        q.pop();
        reachable.insert(front);
        loop(i, 0, dependencies[fileToNodeNum[front]].size()) {
            string next = dependencies[fileToNodeNum[front]][i];
            if (!reachable.count(next)) {
                reachable.insert(next);
                q.push(next);
            }
        }
    }

    for (i=0;i<soln.size();i++) {
        if (reachable.count(soln[i])) {
            cout << soln[i] << endl;
        }
    }
}