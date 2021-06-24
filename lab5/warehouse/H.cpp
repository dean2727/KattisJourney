#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;

bool cmp(const pair<string, int>& l, 
         const pair<string, int>& r) 
{
    if (l.second != r.second)
        return l.second > r.second;

    return l.first < r.first;
} 

int main() {
    int T, N, count;
    string toy;
    cin >> T;

    while (T--) {
        cin >> N;
        map<string, int> toys;
        while (N--) {
            cin >> toy >> count;
            if (toys.count(toy) == 0) {
                toys.insert(make_pair(toy, count));
            }
            else {
                toys[toy] += count;
            }
        }
        cout << toys.size() << "\n";
        // code to sort the map from https://www.techiedelight.com/sort-map-values-cpp/
        // create an empty vector of pairs
        vector<pair<string, int> > vec;
    
        // copy key-value pairs from the map to the vector
        copy(toys.begin(),
                toys.end(),
                back_inserter<vector<pair<string, int> > >(vec));
 
        // sort the vector by increasing order of its pair's second value
        // if second value are equal, order by the pair's first value
        sort(vec.begin(), vec.end(), cmp);
    
        // print the vector
        for (vector<pair<string, int> >::iterator it=vec.begin();it!=vec.end();it++) {
            cout << it->first << " " << it->second << '\n';
        }
        // sort(toys.begin(), toys.end(), cmp);
        
        // for (map<string, int>::iterator x=toys.begin();x!=toys.end();x++){
        //     cout << x->first << " " << x->second << "\n";
        // }
    }

	return 0;
}
