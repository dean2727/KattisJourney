#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// this implements rabin karp
// https://github.com/kth-competitive-programming/kactl/blob/master/content/strings/Hashing.h

struct H {
	typedef uint64_t ull;
	ull x;
    H(ull x=0) : x(x) {}
#define OP(O,A,B) H operator O(H o) { ull r = x; asm \
	(A "addq %%rdx, %0\n adcq $0,%0" : "+a"(r) : B); return r; }
	OP(+,,"d"(o.x)) OP(*,"mul %1\n", "r"(o.x) : "rdx")
	H operator-(H o) { return *this + ~o.x; }
	ull get() const { return x + !~x; }
	bool operator==(H o) const { return get() == o.get(); }
	bool operator<(H o) const { return get() < o.get(); }
};
static const H C = (long long)1e11+3; // (order ~ 3e9; random also ok)

vector<H> getHashes(string& str, int length) {
    vector<H> ret;
	if (str.length() < length) return ret;
	H h = 0, pw = 1;
    for (int i=0;i<length;i++) {
        h = h * C + str[i];
        pw = pw * C;
    }
    ret.push_back(h);
    for (int i=length;i<str.length();i++) {
		ret.push_back(h = h * C + str[i] - pw * str[i-length]);
	}
	return ret;
}

int binarySearch(string str, int left, int right) {
    if (left > right) {
        return right;
    }
    int mid = (left + right) / 2;

    // run rabin karp's algorithm each time to see if there are more than 1 indices a pattern appears in the string
    vector<H> hashes = getHashes(str, mid);

    // sort the hashes, check each pair. if there are 2 or more similar ones, then the substring appears multiple times
    sort(hashes.begin(), hashes.end());
    bool sameHashes = false;
    for (int i=0;i<hashes.size()-1;i++) {
        if (hashes[i] == hashes[i+1]) {
            sameHashes = true;
            break;
        }
    }

    // if its possible for a substring of length mid to appear multiple times, maybe we can search higher
    if (sameHashes) {
        return binarySearch(str, mid+1, right);
    }
    // otherwise, need to search lower
    else {
        return binarySearch(str, left, mid-1);
    }
}

int main() {
    int L;
    cin >> L;
    string line;
    cin >> line;

    // binary search the answer: start with low = 1 and high = L (mid = L/2) for the lengths of the
    // possible substrings that can occur twice. run rabin karp's algorithm each time 
    // to see if there are more than 1 indices a pattern appears in the string
    int low = 1, high = L;
    int ans = binarySearch(line, low, high);
    cout << ans;
}