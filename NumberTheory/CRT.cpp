#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int n;
vector<ll> m(15),r(15); //除数，余数

//位运算实现(a*b)%mod
ll multiple(ll a,ll b,ll mod) {
    a=(a%mod+mod)%mod;
    b=(b%mod+mod)%mod;
    ll res=0;
    while(b) {
        if(b&1) res=(res+a)%mod;
        a=(a+a)%mod;
        b>>=1;
    }
    return res;
}

//求方程ax+by=gcd(a,b)的一个特解
template<typename T>
pair<T,T> exgcd(T a,T b) {
    if(b==0) return {1,0};
    auto [x,y]=exgcd(b,a%b);
    return {y,x-a/b*y};
}
//求a对b的逆元
template<typename T>
T inv(T a,T b) {
    if(gcd(a,b)!=1) return -1;
    auto [x,y]=exgcd(a,b);
    x=(x%b+b)%b;
    return x;
}

//中国剩余定理模板
ll crt() {
    ll lm=1;
    for(int i=1;i<=n;i++) lm*=m[i];
    ll res=0;
    for(int i=1;i<=n;i++) {
        ll c=multiple(multiple(r[i], lm/m[i], lm), inv(lm/m[i],m[i]), lm);
        res=(res+c)%lm;
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>m[i]>>r[i];
    ll ans=crt();
    cout<<ans<<'\n';
    return 0;
}
