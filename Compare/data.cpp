#include <bits/stdc++.h>
using namespace std;
using ll=long long;

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

signed main() {
    ll a=rnd()%1000000;
    ll b=rnd()%1000000;
    cout<<a<<' '<<b<<'\n';
    return 0;
}
