#include <iostream>
#include <numeric>
#include <algorithm>
#include <cstdlib>

using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;

    int numbers[500000];
    int idx[500000];

    for (int i = 0; i < N; ++i) {
        cin >> numbers[i];
        idx[i] = i;
    }

    sort(idx, idx + N, [&numbers](int const &idx1, int const &idx2) -> bool const {return numbers[idx1] < numbers[idx2];});

    int answer = 0;
    for (int i = 0; i < N; ++i) {
        int sorted_pos = i;
        int initial_pos = idx[i];
        int max_diff = N - 1 - i;
        int diff = abs(i - idx[i]);
        answer = max(answer, min(max_diff, diff));
    }

    cout << answer;

    return 0;
}