#include <bits/stdc++.h>
using namespace std;
using ll=long long;

signed main() {
    system("g++ -std=c++20 data.cpp -o data.exe");
    system("g++ -std=c++20 std.cpp -o std.exe");
    system("g++ -std=c++20 solve.cpp -o solve.exe");

    int t=1;
    while(1) {
        cout<<"test: "<<t<<'\n';

        system("data.exe > data.in");
        system("std.exe < data.in > std.out");
        system("solve.exe < data.in > solve.out");
        if(system("fc std.out solve.out > diff.log")) {
            cout<<"Wrong Answer on Test "<<t<<'\n';
            break;
        }

        t++;
    }
    return 0;
}
