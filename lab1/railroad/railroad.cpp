/*
Theta likes to play with her DUPLO railway set. The railway set
she has consists of pieces of straight tracks, curved tracks, Y-shaped 
switches, and X-shaped level junctions, as well as bridges that allow one
track to cross over another. There are also straight tracks that are railroad
crossings to allow car traffic to cross.
To play, she picks a number of X-shaped level junctions and a number of Y-shaped
switches and connects them with straight and curved pieces, using bridges as
necessary. Because the set doesn’t include any bumpers, she wants to build a
closed track, like all the examples shown in the manual that came with the set:

Unfortunately, sometimes, this doesn’t seem to work with the number of X-shaped
level junctions and Y-shaped switches she starts out with.

She quickly figures out exactly when it is possible to build a closed track -
can you figure it out, too?

Write a program that outputs if it is possible to build a railroad that does not
require any bumpers (i.e., which does not have any dead-end tracks).

input:
The input consists of a single test case with two integer numbers 𝑋 (0≤𝑋≤1000)
and 𝑌 (0≤𝑌≤1000) denoting the number of level junctions and switches, respectively.
You may assume that Theta has sufficiently many straight and curved pieces as well
as bridges.

output:
Output possible if she can build a closed track using all level junctions and all
switches without any dead ends, or impossible otherwise.
*/

#include <iostream>

using namespace std;

int main()
{
    int X, Y;
    cin >> X >> Y;
    
    if ((X * 4 + Y * 3) % 2 == 1) {
        cout << "impossible";    
    }
    else {
        cout << "possible";
    }

    return 0;
}