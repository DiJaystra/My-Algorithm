#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//求单个欧拉函数的值
ll euler_phi(ll n) {
    ll ans=n;
    for(ll i=2;i*i<=n;i++) {
        if(n%i==0) {
            ans=ans/i*(i-1);
            while(n%i==0) {
                n/=i;
            }
        }
    }
    if(n>1) ans=ans/n*(n-1);
    return ans;
}

const ll MAXN=1e7;
vector<ll> primes,phi(MAXN);
//线性筛法批量求欧拉函数的值，同时求质数
void get_phi() {
    vector<bool> isPrime(MAXN+1,true);
    isPrime[0]=false;
    isPrime[1]=false;
    phi[1]=1;
    for(ll i=2;i<MAXN;i++) {
        if(isPrime[i]) {
            phi[i]=i-1;
            primes.emplace_back(i);
        }
        for(ll p : primes) {
            ll n=i*p;
            if(n>MAXN) break;
            isPrime[n]=false;
            if(i%p) {
                phi[n]=phi[i]*phi[p];
            }
            else {
                phi[n]=p*phi[i];
                break;
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    get_phi();
    return 0;
}