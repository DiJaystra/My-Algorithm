#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const ll MOD=1e9+7;
const int MAXN=1e7+5;

//快速幂
ll fpow(ll base,ll exp,ll m) {
    ll res=1;
    base%=m;
    while(exp>0) {
        if(exp & 1) res=(res*base) % m;
        base=(base*base)%m;
        exp>>=1;
    }
    return res;
}

vector<ll> fact(MAXN);
//初始化一些数的阶乘
void initFact() {
    fact[0]=fact[1]=1;
    for(ll i=2;i<MAXN;i++) fact[i]=fact[i-1]*i%MOD;
}

//n很大，m较小时
ll C1(ll n,ll m) {
    if(m>n || m<0) return 0;
    ll num1=1;
    for(ll i=n;i>=n-m+1;i--) {
        num1=num1*(i%MOD)%MOD;
    }
    ll num2=fact[m];
    ll inv=fpow(num2,MOD-2,MOD);
    ll res=num1*inv%MOD;
    return res;
}
//n很小
ll C2(ll n,ll m) {
    if(m>n || m<0) return 0;
    return fact[n]*fpow(fact[m],MOD-2,MOD)%MOD*fpow(fact[n-m],MOD-2,MOD)%MOD;
}
//n很大，m也很大，但MOD较小时，用卢卡斯定理
ll C3(ll n,ll m) {
    if(m==0) return 1;
    return C3(n/MOD,m/MOD)*C2(n%MOD,m%MOD)%MOD;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    initFact(); //调用以初始化
    return 0;
}
