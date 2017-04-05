#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

int main () {
    int k;
    cin >> k;
    for (int comb = 0; comb < pow(2, k); comb++) {
        for (int i = 0; i < k; i++) {
            printf("%d", (comb >> i) & 1);
        }
        printf("\n");
    }
}
