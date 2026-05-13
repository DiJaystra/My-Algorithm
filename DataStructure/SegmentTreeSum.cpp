//求和线段树
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int n; //数组长度
vector<ll> arr; //原数组

//线段树模板部分
vector<ll> sum; //区间和
vector<ll> lazy; //懒标记
//线段树初始化
void build(int id,int l,int r) {
    if(l==r) {
        sum[id]=arr[l];
        return;
    }
    int mid=(l+r)>>1;
    build(id<<1,l,mid);
    build(id<<1|1,mid+1,r);
    sum[id]=sum[id<<1]+sum[id<<1|1];
}
//懒标记下发
void pushdown(int id,int l,int r) {
    if(lazy[id]==0) return;
    ll lz=lazy[id];
    int mid=(l+r)>>1;
    sum[id<<1]+=lz*(mid-l+1),sum[id<<1|1]+=lz*(r-mid);
    lazy[id<<1]+=lz,lazy[id<<1|1]+=lz;
    lazy[id]=0;
}
//单点更新
void update(int id,int l,int r,int idx,ll val) {
    if(l==r) {
        sum[id]=val;
        lazy[id]=0;
        return;
    }
    pushdown(id,l,r);
    int mid=(l+r)>>1;
    if(idx<=mid) update(id<<1,l,mid,idx,val);
    else update(id<<1|1,mid+1,r,idx,val);
    sum[id]=sum[id<<1]+sum[id<<1|1];
}
//区间更新
void range(int id,int l,int r,int ql,int qr,ll val) {
    if(ql<=l && r<=qr) {
        sum[id]+=val*(r-l+1);
        lazy[id]+=val;
        return;
    }
    pushdown(id,l,r);
    int mid=(l+r)>>1;
    if(ql<=mid) range(id<<1,l,mid,ql,qr,val);
    if(qr>mid) range(id<<1|1,mid+1,r,ql,qr,val);
    sum[id]=sum[id<<1]+sum[id<<1|1];
}
//区间和查询
ll query(int id,int l,int r,int ql,int qr) {
    if(ql<=l && r<=qr) {
        return sum[id];
    }
    pushdown(id,l,r);
    ll res=0;
    int mid=(l+r)>>1;
    if(ql<=mid) res+=query(id<<1,l,mid,ql,qr);
    if(qr>mid) res+=query(id<<1|1,mid+1,r,ql,qr);
    return res;
}

int main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    arr.resize(n);
    for(int i=0;i<n;i++) cin>>arr[i];

    //线段树初始化
    sum.resize(4*n),lazy.resize(4*n);
    build(1,0,n-1);

    int q;cin>>q;
    while(q--) {
        int op;cin>>op;
        if(op==1) { //区间查询
            int ql,qr;cin>>ql>>qr;
            ql--,qr--;
            cout<<query(1,0,n-1,ql,qr)<<'\n';
        }
        else if(op==2) { //单点修改
            int idx;ll val;cin>>idx>>val;
            idx--;
            update(1,0,n-1,idx,val);
        }
        else if(op==3) { //区间更新
            int ql,qr;ll val;cin>>ql>>qr>>val;
            ql--,qr--;
            range(1,0,n-1,ql,qr,val);
        }
    }
    return 0;
}