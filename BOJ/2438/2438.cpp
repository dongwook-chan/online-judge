#include <iostream>
#include <string>

using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int N;
    cin >> N;
    for(int i = 1; i <= N; ++i){
        cout << string(i, '*') << '\n';
    }
    return 0;
}