#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const ll MAXN=1e7;
vector<ll> primes;

void sieve() {
    vector<bool> isPrime(MAXN+1,true);
    isPrime[0]=false;
    isPrime[1]=false;
    for(ll i=2;i<=MAXN;i++) {
        if(isPrime[i]) {
            primes.emplace_back(i);
        }
        for(ll p : primes) {
            ll n=i*p;
            if(n>MAXN) break;
            isPrime[n]=false;
            if(i % p == 0) {
                break;
            }
        }
    }
}

int main() {
    sieve(); //别忘了这行
    return 0;
}