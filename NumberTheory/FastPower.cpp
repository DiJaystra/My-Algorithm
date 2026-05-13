#include <bits/stdc++.h>
using namespace std;
using ll=long long;
//不带MOD
ll fpow_real(ll base,ll exp) {
    ll res=1;
    while(exp) {
        if(exp & 1) {
            res*=base;
        }
        base*=base;
        exp>>=1;
    }
    return res;
}
//带MOD
const ll MOD=998244353;
ll fpow_mod(ll base,ll exp) {
    ll res=1;
    base%=MOD;
    while(exp>0) {
        if(exp & 1) {
            res=(res*base)%MOD;
        }
        base=(base*base)%MOD;
        exp>>=1;
    }
    return res;
}