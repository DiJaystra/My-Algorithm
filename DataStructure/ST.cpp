#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int n,k; //数组长度，k=log2(n)
vector<ll> a;

//ST表实现模板
vector<vector<ll>> st; //倍增表
//初始化倍增表
void build() {
    st.assign(n,vector<ll>(k+1));
    //st[i][j]:i位置开始，长度为2^j的区间的最大值
    for(int i=0;i<n;i++) {
        st[i][0]=a[i];
    }
    for(int j=1;j<=k;j++) {
        for(int i=0;i+(1<<j)-1<n;i++) {
            st[i][j]=max(st[i][j-1],st[i+(1<<(j-1))][j-1]);
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
    k=log2(n);
    a.resize(n);
    for(int i=0;i<n;i++) cin>>a[i];
    build(); //st表初始化

    int q;cin>>q;
    while(q--) {
        int l,r;cin>>l>>r;
        l--,r--;
        cout<<query(l,r)<<'\n';
    }
    return 0;
}