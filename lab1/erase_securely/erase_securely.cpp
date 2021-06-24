/*
Jon Marius is the computer expert at his company and has now been tasked
to find some software for erasing data properly. It is very important that
the data should not be recoverable afterwards, so it should be overwritten
on the hard drive several times. Unable to find any free program up to the
task, Jon Marius decides to write such a program himself. The user interface
is simple, it only asks for the file to be destroyed and 𝑛, the number of times
it should be overwritten. This number can range from 1 (quick deletion) to 
20 (maximum security). Jon Marius processes the file bit by bit and does not
consider writing a zero where there was already a zero as really overwriting.
So for each of the 𝑛 sweeps, he overwrites each zero with a one, and each 
one with a zero, respectively.

Jon Marius knows that independent testing is important, so he has asked you
to write the verification routine. He will not listen to your objections to
the algorithm so eventually you give in.

input:
The first line of the input contains a single integer 1≤𝑁≤20. The two following
lines each contain a string containing only the characters 0 and 1. The first of
these lines represent the bits of the file before deletion and the second the bits
on the same position on the hard drive after the file has been deleted. The length
of these strings are the same and between 1 and 1000 characters.

output:
Output a single line containing either the words “Deletion succeeded” if each
bit is switched 𝑁 times or “Deletion failed” if this is not the case.
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
    int N;
    cin >> N;
    
    string str1, str2;
    cin >> str1 >> str2;
    
    bool valid = true;
    
    if (N % 2 == 0) {
        for (int i = 0; i < str1.length(); i++) {
            if (str1[i] != str2[i]) {
                valid = false;
                break;
            }
        }
    }
    
    else {
        for (int i = 0; i < str1.length(); i++) {
            if (str1[i] == str2[i]) {
                valid = false;
                break;
            }
        }
    }
    
    if (valid) {
        cout << "Deletion succeeded";
    }
    else {
        cout << "Deletion failed";
    }
}
