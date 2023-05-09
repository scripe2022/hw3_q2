// compile: g++ -o graph_gen graph_gen.cpp -O3 -std=gnu++20 -Wall -Wextra -Wshadow -D_GLIBCXX_ASSERTIONS -ggdb3 -fmax-errors=2 -DLOCAL
// run: ./graph_gen 5 5 2
#include "jngen.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char *argv[]) {
    assert(argc == 4);
    int V = stoi(argv[1]);
    int E = stoi(argv[2]);
    int NUM = stoi(argv[3]);
    auto g = Graph::random(V, E).connected(1).g();
    g.setEdgeWeights(TArray<int>::random(g.m(), 1, NUM));
    cout << g << endl;
}