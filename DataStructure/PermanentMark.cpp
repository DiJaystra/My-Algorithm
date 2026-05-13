//标记永久化的区间修改求和线段树（查询和修改要符合叠加性）
//是区间修改主席树的优化，但适用范围不广
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=1e5+5;
const int MAXT=MAXN*4;
vector<ll> arr(MAXN);

//不是真实的累加和，而是之前的任务中
//不考虑上方范围拦截的任务，只考虑来到当前及往下走的任务
//累加和变成了什么
vector<ll> sum(MAXT);
//不是懒处理标记，只是标记被拦截的任务
vector<ll> add(MAXT);
//建树（原模板相同）
void build(int id,int l,int r) {
    if(l==r) sum[id]=arr[l];
    else {
        int mid=(l+r)>>1;
        build(id<<1,l,mid);
        build(id<<1|1,mid+1,r);
        sum[id]=sum[id<<1]+sum[id<<1|1];
    }
}
//区间更新
void update(int id,int l,int r,int ql,int qr,ll v) {
    int x=max(l,ql),y=min(r,qr); //找交集
    sum[id]+=v*(y-x+1); //相当于提前为抽象的sum完成了pushup
    if(ql<=l && r<=qr) {
        add[id]+=v;
    }
    else {
        int mid=(l+r)>>1;
        if(ql<=mid) update(id<<1,l,mid,ql,qr,v);
        if(qr>mid) update(id<<1|1,mid+1,r,ql,qr,v);
        //不用pushup!
    }
}
//区间求和
ll query(int id,int l,int r,int ql,int qr,ll hist) {
    //hist:来到这个节点的路上，所有标记的和
    if(ql<=l && r<=qr) {
        return sum[id]+hist*(r-l+1);
    }
    ll res=0;
    int mid=(l+r)>>1;
    if(ql<=mid) res+=query(id<<1,l,mid,ql,qr,hist+add[id]);
    if(qr>mid) res+=query(id<<1|1,mid+1,r,ql,qr,hist+add[id]);
    return res;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    int n,q;cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>arr[i];
    build(1,1,n); //建原数
    while(q--) {
        int op;cin>>op;
        if(op==1) { //区间+
            int l,r;ll k;cin>>l>>r>>k;
            update(1,1,n,l,r,k);
        }
        else { //区间和查询
            int l,r;cin>>l>>r;
            cout<<query(1,1,n,l,r,0)<<'\n';
        }
    }
    return 0;
}
