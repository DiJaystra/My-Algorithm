//区间修改主席树的经典实现
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=1e5+5; //数组最长大小
//总节点数较玄学，这里是(n*4+m*(4*logn))
const int MAXT=MAXN*80;
int n,m,t=0; //数组长度，查询数量，时间戳
vector<int> arr(MAXN); //原数组

vector<int> root(MAXN); //版本v的根节点
//节点i的左右孩子
vector<int> lch(MAXT),rch(MAXT);
//累加和信息,懒标记累加和信息
vector<ll> sum(MAXT),add(MAXT);
int cnt=0;
//克隆一个节点
int clone(int id) {
    int now=++cnt;
    lch[now]=lch[id];
    rch[now]=rch[id];
    sum[now]=sum[id];
    add[now]=add[id];
    return now;
}
//pushup
void up(int id) {
    sum[id]=sum[lch[id]]+sum[rch[id]];
}
//区间修改，附上懒标记
void lazy(int id,ll v,int n) {
    sum[id]+=v*n;
    add[id]+=v;
}
//pushdown
void down(int id,int ln,int rn) {
    //懒标记造成的孩子节点修改也会新建节点
    if(add[id]!=0) {
        lch[id]=clone(lch[id]);
        rch[id]=clone(rch[id]);
        lazy(lch[id],add[id],ln);
        lazy(rch[id],add[id],rn);
        add[id]=0;
    }
}
//建原树
int build(int l,int r) {
    int now=++cnt;
    add[now]=0;
    if(l==r) sum[now]=arr[l];
    else {
        int mid=(l+r)>>1;
        lch[now]=build(l,mid);
        rch[now]=build(mid+1,r);
        up(now);
    }
    return now;
}
//区间+（除了返回生成的新结点，其它与线段树模板相同）
int update(int id,int l,int r,int ql,int qr,ll v) {
    int now=clone(id);
    if(ql<=l && r<=qr) { //区间全包，则修改区间和并带上懒标记
        lazy(now,v,r-l+1);
    }
    else {
        int mid=(l+r)>>1;
        down(now,mid-l+1,r-mid);
        if(ql<=mid) {
            lch[now]=update(lch[now],l,mid,ql,qr,v);
        }
        if(qr>mid) {
            rch[now]=update(rch[now],mid+1,r,ql,qr,v);
        }
        up(now);
    }
    return now;
}
//区间查询（与原模板结构完全相同）
ll query(int id,int l,int r,int ql,int qr) {
    if(ql<=l && r<=qr) {
        return sum[id];
    }
    int mid=(l+r)>>1;
    down(id,mid-l+1,r-mid);
    ll res=0;
    if(ql<=mid) res+=query(lch[id],l,mid,ql,qr);
    if(qr>mid) res+=query(rch[id],mid+1,r,ql,qr);
    return res;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>arr[i];
    root[0]=build(1,n); //建原树初始化
    while(m--) {
        char op;cin>>op;
        if(op=='C') { //以版本t为基础，[x,y]区间加z，t自增1
            int x,y,z;cin>>x>>y>>z;
            root[t+1]=update(root[t],1,n,x,y,z);
            t++;
        }
        else if(op=='Q') { //查询版本t的[x,y]区间和
            int x,y;cin>>x>>y;
            cout<<query(root[t],1,n,x,y)<<'\n';
        }
        else if(op=='H') { //查询版本z的[x,y]区间和
            int x,y,z;cin>>x>>y>>z;
            cout<<query(root[z],1,n,x,y)<<'\n';
        }
        else { //修改时间戳t
            cin>>t;
        }
    }
    return 0;
}
