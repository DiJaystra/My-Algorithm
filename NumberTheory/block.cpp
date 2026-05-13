#include <bits/stdc++.h>
using namespace std;
using ll=long long;

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    ll n;cin>>n;
    ll ans=0;
    ll l=1;
    while(l<=n) {
        ll r=n/(n/l);
        ans+=(r-l+1)*(n/l);
        l=r+1;
    }
    cout<<ans<<'\n';
    return 0;
}