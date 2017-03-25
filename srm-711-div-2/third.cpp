#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

#define MODULO 1000000007

class Edge {
public:
    int v1;
    int v2;
    int combinations;
    Edge (int v1, int v2, int combinations) {
        this->v1 = v1;
        this->v2 = v2;
        this->combinations = combinations;
    }

};

typedef vector<vector<bool> > MAT;

class TreeMovingDiv2 {
public:
    vector< vector<int> > generateAdjacencyMatrix (int n, int root, int a, int b, int c) {
        MAT mat;
        for (int i = 0; i < n; i++) {
            mat.push_back(vector<int>(n, false));
        }

        vector<int> X(n-1);
        X[0] = c;
        for (int k = 1; k <= n-2; k++) {
            X[k] = (a * X[k-1] + b) % MODULO;
        }
        for (int j = 0; j <= n-2; j++) {
            int v1 = (root + j + 1) % n;
            int v2 = (root + (X[j] % (j + 1))) % n;
            mat[v1][v2] = true;
            mat[v2][v1] = true;
        }
    }

    int count(int n, vector <int> roots, vector <int> a, vector <int> b, vector <int> c) {
        vector<MAT> matrices;
        for (int i = 0; i < roots.size(); i++) {
            matrices.push_back(generateAdjacencyMatrix(n, roots[i], a[i], b[i], c[i]));
        }

        vector<Edge> front;

        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                if (matrices[0][i][j]) {
                    front.push_back(Edge(i, j, 1));
                }
            }
        }

        // TODO: finish! Uff, It should be simpler than what I have in mind, check solutions when they publish them.

        /**
         * Idea: If I remove edge (v1, v2) from tree T and pass it to tree T+1, there are two possible situations:
         * 1. that edge already exists in T+1, which means T+1 will also have to remove that edge and pass it on.
         * 2. that edge does not exist in T+1, which means it creates a cycle in T+1. In order to break the cycle,
         *    I can pick any of the edges on path from v1 to v2, remove it and pass it on.
         * Now I know for each edge from T, which edges I can/have to remove from T+1 as a consequence of that.
         * My idea is to have a "front" of edges and active tree.
         * At start it would contain all edges from the first tree, and active tree would be the second.
         * For each edge from the front, we look at active tree and add use observation above to determine which edges from it can be passed on, in regard to chosen edge from the front. Those edges are added to the new front. If one edge is detected multiple times in this way, those times are counted. That way we can get that one edge has 32 ways to become a part of the front. Actually, if edge e3 can be picked as a consequence from picking e1 and e2 in previous tree/front, where e1 had 20 ways to come to it and e2 has 42 ways to come to it, the e3 would then have 20+42=62 ways to be picked. So it would be stored in new front with that number.
         * The tricky part seeems to be closing the cycle! We know for every edge from the last tree/front in how many ways is it possible to get to it being removed, but certain ways can prohibit certain moves in the last <-> first tree relationship. What we could do, is not only remember for each edge in the front in how many ways can we get to it, but in how many ways can we get to it if we started with certain edge in the first tree. That would mean that in a front, for each edge, we we would remember up to n numbers.

         So one edge in the fron would look like this:
         class Edge {
           public:
           int v1;
           int v2;
           vector<vector<int> > combinationsPerStartEdge;
         }

         Where combinationsPerStartEdge[i][j] would mean: in how many ways can I get to this edge if I started from the edge (i, j) in the first tree? I used matrix but we could use some less sparse structure for this, like map.

         */
    }
};
