/*
Your favourite public transport company LS (we cannot use their real
name here, so we permuted the letters) wants to change signs on all bus
stops. Some bus stops have quite a few buses that stop there and listing
all the buses takes space. However, if for example buses 141, 142, 143
stop there, we can write 141–143 instead and this saves space. Note that
just for two buses this does not save space.

You are given a list of buses that stop at a bus stop. What is the shortest representation of this list?

input:
The first line of the input contains one integer 𝑁,1≤𝑁≤1000, the number
of buses that stop at a bus stop. Then next line contains a list of 𝑁
space separated integers between 1 and 1000, which denote the bus numbers.
All numbers are distinct.

output:
Print the shortest representation of the list of bus numbers. Use the
format as in the example, separate numbers with single spaces and output
them in sorted order.
*/

#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

int main()
{
    int N;
    cin >> N;
    
    vector<int> nums;
    
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        nums.push_back(num);
    }
    
    // Bubble sort the vector
    int i, j;
    for (i = 0; i < nums.size() - 1; i++) {
        for (j = 0; j < nums.size() - i - 1; j++) {
            if (nums.at(j) > nums.at(j + 1)) {
                iter_swap(nums.begin() + j, nums.begin() + j + 1);
            }
        }
    }
    
    //bool increase1 = false;
    while (!nums.empty()) {
        if (nums.size() == 1) {
            cout << nums.at(0);
            nums.erase(nums.begin(), nums.begin() + 1);
        }
        else if (nums.size() == 2) {
            cout << nums.at(0) << " " << nums.at(1);
            nums.erase(nums.begin(), nums.begin() + 2);
        }
        else {
            if (nums.at(1) - 1 == nums.at(0) && nums.at(2) - 2 == nums.at(0)) {
                int firstNum = nums.at(0);
                int lastNum = nums.at(2);
                int x = 3;
                bool continueSequence = x < nums.size();
                while (continueSequence) {
                    if (x < nums.size()) {
                        if (nums.at(x) - x == nums.at(0)) {
                            lastNum = nums.at(x);
                            x++;    
                        }
                        else {
                            continueSequence = false;
                        }
                    }
                    else {
                        continueSequence = false;
                    }
                }
                
                cout << firstNum << "-" << lastNum;
                nums.erase(nums.begin(), nums.begin() + x);
                if (nums.size() != 0) {
                    cout << " ";
                }
            }
            else {
                cout << nums.at(0) << " ";
                nums.erase(nums.begin(), nums.begin() + 1);
            }
        }
    }

    return 0;
}