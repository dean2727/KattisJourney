// Online C++ compiler to run C++ program online
#include <iostream>
#include <set>
#include <algorithm>
#include <vector>
using namespace std;
int main() {
    set<string> x;
    set<string> y;
    vector<string> v(6);  // option 1: store result in vector
    set<string> s;  // option 2: store result in set
    
    x.insert("bob");
    x.insert("sue");
    x.insert("joe");
    
    y.insert("bob");
    y.insert("sal");
    y.insert("cob");
    
    // option 1
    vector<string>::iterator it = set_union(x.begin(), x.end(), y.begin(), y.end(), v.begin());
    // option 2
    set_union(x.begin(), x.end(), y.begin(), y.end(), inserter(s, s.end()));
    
    for (int i = 0; i < v.size(); i++) {
        cout << v[i] << endl;
    }
    return 0;
}