#include <iostream>
#include <string>

using namespace std;

int main() {
    int N;
    cin >> N;

    for (int i = N - 1; i >= 1; --i)
        cout << string(i, '*') << '\n';

    return 0;
}