#include <stack>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main() {
    int N = 0;
    cin >> N;

    int stackNumber = 0, v = 0, w = 0;
    char type;
    vector<stack<int> > stacks;

    // In the beginning of the game, he has an empty stack denoted with number 0
    cin >> type >> v;
    stack<int> initStack;
    initStack.push(0);
    stacks.push_back(initStack);

    for (int i=1;i<N;i++) {
        cin >> type;

        // get existing stack, copy it
        stack<int> stackCopy = stacks[i - 1];

        cin >> v;

        // type 1: push onto stack
        if (type == 'a') {
            stackCopy.push(v);
        }

        // type 2: remove from the top
        else if (type == 'b') {
            int removedNum = stackCopy.top();
            stackCopy.pop();
            cout << removedNum << endl;
        }

        else {
            cin >> w;

            stack<int> stackv = stacks[v];
            stack<int> stackw = stacks[w];

            // get how many different elements there are in stacks v and w
            set<int> uniqueStackElements;
            int loopsv = stackv.size(), loopsw = stackw.size();
            for (int j=0;j<loopsv;j++) {
                uniqueStackElements.insert(stackv.top());
                stackv.pop();
            }
            for (int j=0;j<loopsw;j++) {
                uniqueStackElements.insert(stackw.top());
                stackw.pop();
            }

            cout << uniqueStackElements.size() << endl;
        }

        stacks.push_back(stackCopy);
    }
}