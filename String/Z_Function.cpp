#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //字符串最长长度

int n; //字符串长度
string s; //字符串
int z[MAXN]; //z函数数组

//计算Z函数
void getZ() {
    z[0]=n; //原串跟原串完全匹配
    int r=0; //匹配右边界
    int c=0; //匹配中心
    //计算z[1]...z[n-1]
    for(int i=1;i<n;i++) {
        //基础长度
        int len = (r>i) ? min(z[i-c],r-i) : 0;
        //扩展长度
        while(i+len<n && s[i+len]==s[len]) {
            len++;
        }
        z[i]=len;
        //如果匹配右边界被推向更远
        if(i+len>r) {
            r=i+len;
            c=i;
        }
    }
}

signed main() {
    cin>>s;
    n=s.size();

    getZ();
    for(int i=0;i<n;i++) cout<<z[i]<<' ';
    cout<<'\n';
    return 0;
}