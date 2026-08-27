//st表实现静态数组查询区间最大值操作
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //最大数组长度
const int LOG=20; //2^20 > 1e5

int n; //数组长度
int q; //查询次数
ll a[MAXN]; //原数组

//ST表实现模板
ll st[MAXN][LOG]; //倍增表

//初始化倍增表
void build() {
    //st[i][j]:i位置开始，长度为2^j的截断区间的最大值
    for(int i=1;i<=n;i++) {
        st[i][0]=a[i];
    }
    for(int j=1;j<LOG;j++) {
        for(int i=1;i<=n;i++) {
            st[i][j]=st[i][j-1];
            int jump=i+(1<<(j-1));
            if(jump<=n) {
                st[i][j]=max(st[i][j],st[jump][j-1]);
            }
        }
    }
}
ll query(int l,int r) {
    int len=r-l+1;
    int loglen=log2(len);
    ll res=max(st[l][loglen],st[r-(1<<loglen)+1][loglen]);
    return res;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    build(); //st表初始化

    cin>>q;
    while(q--) {
        int l,r;cin>>l>>r;
        cout<<query(l,r)<<'\n';
    }
    return 0;
}