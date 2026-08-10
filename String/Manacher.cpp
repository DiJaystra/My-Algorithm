#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //原串最长长度

int n,nn; //原串长度，扩展串长度
string s,ss; //原串，扩展串
int p[MAXN<<1]; //扩展串的回文半径数组

//预处理扩展串
void expand() {
    ss.clear();
    nn=2*n+1;
    //偶数位置填虚字符，奇数位置填实字符
    for(int i=0,j=0;i<nn;i++) {
        ss += (i&1)==0 ? '#' : s[j++];
    }
}

//Manacher算法，返回字符串s的最长回文子串长度
int manacher() {
    int longest=0; //最长回文子串长度
    int r=0; //回文覆盖最右边界
    int c=0; //回文中心
    //逐位置求回文半径
    for(int i=0;i<nn;i++) {
        //基础长度
        //对于情况1，不包含，长度就是1，然后在while中扩展
        //对于情况2.1和2.2，min数组统一处理
        //对于情况2.3，先初始为p[2*c-i]（其实p[2*c-i]==r-i）
        //然后再在while中试探性扩展
        int len = (r>i) ? min(p[2*c-i],r-i) : 1;
        //扩展长度
        //对于情况1和情况2.3，扩展是必要的
        //对于情况2.1和2.2，无法扩展，但也就试探一下
        //不影响时间复杂度
        while(i+len<nn && i-len>=0 && ss[i+len]==ss[i-len]) {
            len++;
        }
        p[i]=len;
        //如果回文覆盖最右边界被推向更远
        if(i+len>r) {
            r=i+len;
            c=i;
        }
        longest=max(longest,len);
    }
    //回文半径-1==真实回文长度
    return longest-1;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>s;
    n=s.size();

    expand();
    int ans=manacher();
    cout<<ans<<'\n';
    return 0;
}