#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//求单个欧拉函数的值
ll euler_phi(ll x) {
    //欧拉函数的值初始化为x
    ll res=x;
    //对x进行质因数分解
    for(ll d=2;d*d<=x;d++) {
        if(x%d==0) {
            //遇到一个因数，对答案贡献*((d-1)/d)
            res=res/d*(d-1);
            while(x%d==0) {
                x/=d;
            }
        }
    }
    if(x>1) res=res/x*(x-1);
    return res;
}

const int MAXN=1e7;
vector<int> primes; //质数数组
int phi[MAXN]; //欧拉函数的值
//线性筛法批量求欧拉函数的值，同时求质数
void get_phi() {
    vector<bool> isPrime(MAXN+1,true);
    isPrime[0]=false;
    isPrime[1]=false;
    phi[1]=1;
    for(int i=2;i<MAXN;i++) {
        if(isPrime[i]) {
            phi[i]=i-1;
            primes.emplace_back(i);
        }
        for(int p : primes) {
            ll num=(ll)i*p;
            if(num>MAXN) break;
            isPrime[num]=false;
            //i不能被质数p整除
            if(i%p) {
                //此时i和p互质
                //于是就有欧拉函数的积性
                phi[num]=phi[i]*phi[p];
            }
            //i能被质数p整除
            else {
                //此时i含有num的所有素因子
                //也就是说num不止一个p因子
                //对比公式即可得到下列递推式
                phi[num]=p*phi[i];
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