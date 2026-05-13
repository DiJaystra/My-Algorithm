//单点修改+区间和查询
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int MAXN=2e5+5;
int n;
vector<ll> a(MAXN);
//树状数组模板
vector<ll> tree(MAXN);
int lowbit(int x) { //取x的最低非0位
    return x&-x;
}
void add(int idx,ll val) { //idx位置的数+val
    while(idx<=n) {
        tree[idx]+=val;
        idx+=lowbit(idx);
    }
}
void build() { //初始化树状数组
    for(int i=1;i<=n;i++) {
        add(i,a[i]);
    }
}
ll query(int idx) { //前缀和查询(1~idx)
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
    build();

    int q;cin>>q;
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
