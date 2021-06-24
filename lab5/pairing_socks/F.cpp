#include <iostream>
#include <stack>
#include <cstdlib>
using namespace std;

typedef stack<int> s;
int main() {
	int sock, n, moves = 0;
    s socks;
    s other;
    bool impossible = true;
    cin >> n;

    for (int i=0;i<2*n;i++) {
        cin >> sock;
        socks.push(sock);
    }

    // put socks on other stack, checking if sock below is same type
    other.push(socks.top());
    socks.pop();
    moves++;
    while (!socks.empty()) {
        moves++;
        // if match (and not empty), remove from other
        if (!other.empty() && other.top() == socks.top()) {
            other.pop();
        }
        else {
            other.push(socks.top());
        }
        socks.pop();
    }

    if (socks.empty() && other.empty()) {
        impossible = false;
    }
    if (impossible) {
        cout << "impossible";
    }
    else {
        cout << moves;
    }
    
	return 0;
}
