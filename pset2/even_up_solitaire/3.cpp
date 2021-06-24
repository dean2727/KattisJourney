#include <iostream>
#include <list>
using namespace std;

int main() {
    int n = 0;
    cin >> n;

    if (n == 1) {
        cout << "1";
        return 0;
    }

    list<int> nums;
    int num = 0;
    for (int i=0;i<n;i++) {
        cin >> num;
        nums.push_back(num);
    }

    list<int>::iterator it1 = nums.begin();
    list<int>::iterator it2 = next(it1, 1);

    bool removed = false;
    if ((*it1 + *it2) % 2 == 0) {
        nums.erase(it1);
        nums.erase(it2);
        removed = true;
    }

    // continually iterate through the list, removing pairs until either 
    // the list is empty or no more valid pairs
    while (nums.size() > 1) {
        // reset iterators if removed
        if (removed) {
            removed = false;
            it1 = nums.begin();
            it2 = next(it1, 1);
        }

        while ((*it1 + *it2) % 2 != 0 && it2 != nums.end()) {
            it1 = it2;
            advance(it2, 1);
        }

        if (it2 != nums.end()) {
            nums.erase(it1);
            nums.erase(it2);
            removed = true;
        }

        // if we get here, and nothing was removed, no cards were drawn
        if (!removed) {
            break;
        }
    }

    cout << nums.size() << endl;
}