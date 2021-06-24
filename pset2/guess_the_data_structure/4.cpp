#include <iostream>
#include <stack>
#include <queue>
#include <set>
using namespace std;

int main() {
    int n = 0, n1 = 0, x = 0;

    while (cin >> n) {
        stack<int> s;
        queue<int> q;
        priority_queue<int> pq;
        bool isStack = false, isQueue = false, isPriorityQueue = false;
        bool stackDifferentSeen = false, queueDifferentSeen = false, priorityQueueDifferentSeen = false;
        int numAdded = 0, numRemoved = 0;

        for (int i=0;i<n;i++) {
            cin >> n1 >> x;

            if (n1 == 1) {
                s.push(x);
                q.push(x);
                pq.push(x);
                numAdded++;
            }

            else if (n1 == 2 && numAdded > numRemoved) {

                // they are these data structures, so long as no difference has been encountered
                if (!stackDifferentSeen && s.top() == x) {
                    isStack = true;
                }
                if (!queueDifferentSeen && q.front() == x) {
                    isQueue = true;
                }
                if (!priorityQueueDifferentSeen && pq.top() == x) {
                    isPriorityQueue = true;
                }

                // if a difference is encountered, can no longer be that data structure
                if (s.top() != x) {
                    stackDifferentSeen = true;
                }
                if (q.front() != x) {
                    queueDifferentSeen = true;
                }
                if (pq.top() != x) {
                    priorityQueueDifferentSeen = true;
                }

                s.pop();
                q.pop();
                pq.pop();
                numRemoved++;
            }

            else {
                numRemoved++;
            }
        }
        if (stackDifferentSeen) {
            isStack = false;
        }
        if (queueDifferentSeen) {
            isQueue = false;
        }
        if (priorityQueueDifferentSeen) {
            isPriorityQueue = false;
        }

        // unsure if more than 1 of the data structures
        if (numRemoved > numAdded) {
            cout << "impossible\n";
        }
        else if ((isStack && isQueue) || (isStack && isPriorityQueue) || (isQueue && isPriorityQueue) ||
        (isStack && isQueue && isPriorityQueue) || (numAdded > 0 && numRemoved == 0)) {
            cout << "not sure" << endl;
        }
        else if (isStack) {
            cout << "stack\n";
        }
        else if (isQueue) {
            cout << "queue\n";
        }
        else if (isPriorityQueue) {
            cout << "priority queue\n";
        }
        else {
            cout << "impossible\n";
        }
    }
}