//快速求出字符串s[l...r]的哈希值
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //最大字符串长度
const ll BASE=727; //进制数
const ll MOD1=1000000033; //模数1
const ll MOD2=1000000097; //模数2

int n; //字符串长度
string s; //字符串

//pow1[i]：base的i次方对MOD1取模后的值
ll pow1[MAXN];
//pow2[i]：base的i次方对MOD2取模后的值
ll pow2[MAXN];
//pref1[i]：前缀串s[1...i]的在MOD1下的哈希值
ll pref1[MAXN];
//pref2[i]：前缀串s[1...i]的在MOD2下的哈希值
ll pref2[MAXN];

//初始化pow数组
void initPow() {
    pow1[0]=pow2[0]=1;
    for(int i=1;i<MAXN;i++) {
        pow1[i]=(pow1[i-1]*BASE)%MOD1;
        pow2[i]=(pow2[i-1]*BASE)%MOD2;
    }
}

//计算pref数组
void prepare() {
    for(int i=1;i<=n;i++) {
        pref1[i]=(pref1[i-1]*BASE+(ll)s[i])%MOD1;
        pref2[i]=(pref2[i-1]*BASE+(ll)s[i])%MOD2;
    }
}

//获取字符串s[l...r]在MOD1的哈希值
ll hash1(int l,int r) {
    return ((pref1[r]-pref1[l-1]*pow1[r-l+1]%MOD1)%MOD1+MOD1)%MOD1;
}
//获取字符串s[l...r]在MOD2的哈希值
ll hash2(int l,int r) {
    return ((pref2[r]-pref2[l-1]*pow2[r-l+1]%MOD2)%MOD2+MOD2)%MOD2;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    initPow(); //初始化power数组
    cin>>s;
    n=s.size();
    s=" "+s;
    prepare(); //计算pref数组

    int q;cin>>q;
    for(int i=1;i<=q;i++) {
        int l,r;cin>>l>>r;
        cout<<hash1(l,r)<<' '<<hash2(l,r)<<'\n';
    }
    return 0;
}
