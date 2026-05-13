#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//带余数除法
pair<ll,ll> divide(ll x, ll y) {
    ll r=x%y;if(r<0) r+=y;
    return {(x-r)/y,r};
}

// 计算 sum_{i=0}^{n} floor((a*i + b) / c)
ll floor_sum(ll a, ll b, ll c, ll n) {
    if(n<0) return 0;
    if(c==0) return 0;
    if(c<0) {
        a=-a,b=-b,c=-c;
    }
    auto [q1,r1]=divide(a, c);
    auto [q2,r2]=divide(b, c);
    if(a<0 || b<0 || a>=c || b>=c) {
        return n*(n+1)/2*q1+(n+1)*q2+floor_sum(r1, r2, c, n);
    }
    ll m=divide(a*n+b,c).first;
    if(m==0) return 0;
    return m*n-floor_sum(c,c-b-1,a,m-1);
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    ll a,b,c,n;cin>>a>>b>>c>>n;
    ll ans=floor_sum(a,b,c,n);
    cout<<ans<<'\n';
    return 0;
}