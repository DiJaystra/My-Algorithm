#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=1e7;

vector<int> primes; //质数数组

//欧拉筛法求质数
void sieve() {
    vector<bool> isPrime(MAXN+1,true);
    isPrime[0]=false;
    isPrime[1]=false;
    for(int i=2;i<=MAXN;i++) {
        if(isPrime[i]) {
            primes.emplace_back(i);
        }
        for(int p : primes) {
            ll num=(ll)i*p;
            if(num>MAXN) break;
            isPrime[num]=false;
            //关键优化，保证所有合数只被最小质因子剔除
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