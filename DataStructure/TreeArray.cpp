//树状数组实现单点修改+区间和查询
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //最大数组长度

int n; //数组长度
int q; //查询数量
ll a[MAXN]; //原数组

//树状数组模板
ll tree[MAXN];

//取x最低非0位的值
int lowbit(int x) {
    return x&-x;
}
//idx位置的数+=val
void add(int idx,ll val) {
    while(idx<=n) {
        tree[idx]+=val;
        idx+=lowbit(idx);
    }
}
//初始化树状数组
void build() {
    for(int i=1;i<=n;i++) {
        add(i,a[i]);
    }
}
//前缀和查询(1~idx)
ll query(int idx) {
    ll res=0;
    while(idx) {
        res+=tree[idx];
        idx-=lowbit(idx);
    }
    return res;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i]; //一定要使用1-index

    //初始化树状数组
    build();

    cin>>q;
    while(q--) {
        int op;cin>>op;
        if(op==1) { //区间和查询
            int l,r;cin>>l>>r;
            cout<<query(r)-query(l-1)<<'\n';
        }
        else { //单点增加
            int idx;ll x;cin>>idx>>x;
            add(idx,x);
        }
    }
    return 0;
}
