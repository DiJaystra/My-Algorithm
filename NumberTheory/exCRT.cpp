#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=1e5+5;
int n;
vector<ll> m(MAXN),r(MAXN); //除数，余数

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

//扩展中国剩余定理模板
ll excrt() {
    //初始的ans=1*x+0
    ll lm=1,tail=0;
    for(int i=1;i<=n;i++) {
        //原方程:ans=lm*x+tail
        //新方程:ans=m[i]*y+r[i]
        //用扩展欧几里得解方程:lm*x+m[i]*y=r[i]-tail,得最小非负数解x0
        ll a=lm,b=m[i],c=r[i]-tail;
        //可以让a,c都对b取模，不影响x的最小非负整数解，但影响y的最小非负整数解
        ll g=__gcd(a,b);
        if(c%g != 0) return -1;
        auto [x0,y0]=exgcd(a,b);
        x0=multiple(x0,c/g,b/g);
        //升级之后ans=(lm*b/g)*x+(lm*x0+tail)
        ll nlcm=b/g*lm;
        tail=(multiple(lm,x0,nlcm)+tail)%nlcm;
        lm=nlcm;
    }
    return tail;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>m[i]>>r[i];
    cout<<excrt()<<'\n';
    return 0;
}
