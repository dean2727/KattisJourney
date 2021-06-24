/*
Mirko has a younger brother, Filip, who just started going to school and is having
trouble with numbers. To help him get the hang of the number scale, his teacher
writes two three-digit numbers. She asks Filip to compare those numbers, but
instead of interpreting them with the leftmost most significant digit, he needs
to interpret them the other way around, with the most significant digit being the
rightmost one. He then has to tell the teacher the larger of the two numbers.

Write a program that will check Filip’s answers.

input:
The first and only line of input contains two three-digit numbers, 𝐴 and 𝐵.
𝐴 and 𝐵 will not be equal and will not contain any zeroes.

output:
The first and only line of output should contain the larger of the numbers
in the input, compared as described in the task. The number should be written
reversed, to display to Filip how he should read it.
*/

#include <iostream>
#include <string>
using namespace std;

int main()
{
    int A, B;
    cin >> A >> B;
  
    int rightmostA = A % 10;
    int rightmostB = B % 10;
    
    int middleA = (A / 10) % 10;
    int middleB = (B / 10) % 10;
    
    int leftA = A / 100;
    int leftB = B / 100;
    
    string reversedA = to_string(rightmostA) + to_string(middleA) + to_string(leftA);
    string reversedB = to_string(rightmostB) + to_string(middleB) + to_string(leftB);
    
    if (rightmostA > rightmostB) {
        cout << reversedA;
    }
    else if (rightmostB > rightmostA) {
        cout << reversedB;
    }
    else if (middleA > middleB) {
        cout << reversedA;
    }
    else if (middleB > middleA) {
        cout << reversedB;
    }
    else if (leftA > leftB) {
        cout << reversedA;
    }
    else {
        cout << reversedB;
    }

    return 0;
}