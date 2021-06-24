#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

int main() {
    // get input
    int N = 0, K = 0, idx;
    cin >> N >> K;

    vector<pair<int, string>> itemsAndStores;

    int i;
    string item;
    for (int idx; idx < K; idx++) {
        cin >> i >> item;
        itemsAndStores.push_back(make_pair(i, item);
    }

    int M = 0;
    cin >> M;
    string sisItem;
    vector<string> sisItems;
    for (idx = 0; idx < M; idx++) {
        cin >> sisItem;
        sisItems.push_back(sisItem);
    }

    // loop through the items sis bought
    for (idx = 0; idx < sisItems.size(); idx++) {
        // if this item is not available at the idx store, impossible
        for (int store = 0; store < itemsAndStores.count(idx); store++) {

        }
        if (sisItems[idx])
    }


    // if the item sis bought is located 
}