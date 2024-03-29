#include <iostream>

using namespace std;

bool input_ctr_natural[2000001];
bool *input_ctr = input_ctr_natural + 1000000;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    while(N--){
        int input;
        cin >> input;
        input_ctr[input] = true;
    }

    for (int i = -1000000; i < 1000001; ++i){
        if (input_ctr[i]) {
            cout << i << '\n';
        }
    }

    return 0;
}