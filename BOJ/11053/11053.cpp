#include <iostream>
#include <cstring>
#include <algorithm>

#define MAX_SIZE 1000
#define NOT_MEMOIZED -1

using namespace std;

unsigned int table[MAX_SIZE + 1];
unsigned int A[MAX_SIZE + 1];

void init_table() {
    memset(table, NOT_MEMOIZED, sizeof(table));
}

unsigned int lookup(int n) {
    // base case
    if(n == 1) return 1;

    // memoized
    if(table[n] != NOT_MEMOIZED) return table[n];

    // not memoized
    table[n] = 1;
    for(int i = 1; i < n; ++i){
        if(A[i] < A[n]) {
            table[n] = max(table[n], lookup(i) + 1);
        }
    }
    return table[n];
}

int main() {
    init_table();

    int N;
    cin >> N;
    for(int i = 1; i <= N; ++i) {
        cin >> A[i];
    }

    cout << lookup(N);

    return 0;
}