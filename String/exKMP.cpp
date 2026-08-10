//计算字符串a每个后缀，分别与字符串b整体
//的最长相同前缀长度
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e7+5; //字符串最长长度

int n,m; //字符串a,b各自长度
string a,b;

//字符串b的z数组
int z[MAXN];
//a对b的e数组
int e[MAXN];

//计算b的Z函数
void getZ() {
    z[0]=m; //原串跟原串完全匹配
    int r=0; //匹配右边界
    int c=0; //匹配中心
    //计算z[1]...z[n-1]
    for(int i=1;i<m;i++) {
        //基础长度
        int len = (r>i) ? min(z[i-c],r-i) : 0;
        //扩展长度
        while(i+len<m && b[i+len]==b[len]) {
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

//计算a对b的E函数
void getE() {
    int r=0; //匹配右边界
    int c=0; //匹配中心
    //计算e[0]...e[n-1]
    for(int i=0;i<n;i++) {
        //基础长度
        int len = (r>i) ? min(z[i-c],r-i) : 0;
        //扩展长度
        while(i+len<n && len<m && a[i+len]==b[len]) {
            len++;
        }
        e[i]=len;
        //如果匹配右边界被推向更远
        if(i+len>r) {
            r=i+len;
            c=i;
        }
    }
}

signed main() {
    cin>>a>>b;
    n=a.size();
    m=b.size();

    getZ();
    getE();
    
    for(int i=0;i<m;i++) cout<<z[i]<<' ';
    cout<<'\n';
    for(int i=0;i<n;i++) cout<<e[i]<<' ';
    cout<<'\n';
    return 0;
}