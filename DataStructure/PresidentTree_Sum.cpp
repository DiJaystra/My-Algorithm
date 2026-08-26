//一个初始数组，单点修改产生新版本
//查询某版本的区间和
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//最大数组长度
const int MAXN=1e6+5;
//最大版本数量
const int MAXV=1e6+5;
//主席树最大节点数量
//初始线段树最多2n-1个节点；每次修改最多新增ceil(log2 n)+1=21个节点
//修改次数不超过1e6，所以最多约(2*1e6+21*1e6)个节点
const int MAXT=MAXN*23;

//数组长度，查询数量
int n,q;

//原数组
ll arr[MAXN];
//head[i]：版本号i的头节点
int head[MAXV];
//节点i的左儿子和右儿子节点编号
int lch[MAXT],rch[MAXT];
//sum[i]：节点i所代表区间的和
ll sum[MAXT];
//版本编号计数
int version=0;
//主席树空间节点计数
int cntv=0;

//克隆一个节点
int clone(int id) {
    int h=++cntv;
    lch[h]=lch[id];
    rch[h]=rch[id];
    sum[h]=sum[id];
    return h;
}
//汇总节点信息
void pushup(int id) {
    sum[id]=sum[lch[id]]+sum[rch[id]];
}
//初始化主席树
int build(int l,int r) {
    //头结点编号分配
    int h=++cntv;
    //如果来到的是叶子节点
    if(l==r) {
        sum[h]=arr[l];
        return h;
    }
    //非叶节点
    int mid=(l+r)>>1;
    //左右孩子构建
    lch[h]=build(l,mid);
    rch[h]=build(mid+1,r);
    //汇总该节点信息
    pushup(h);
    //将头结点返回给上级节点连接
    return h;
}
//单点更新数组
int update(int id,int l,int r,int idx,ll val) {
    //拷贝原节点信息
    int h=clone(id);
    //如果来到的是叶子节点
    if(l==r) {
        sum[h]=val;
        return h;
    }
    //非叶节点
    int mid=(l+r)>>1;
    //去往要修改的节点
    if(idx<=mid) lch[h]=update(lch[h],l,mid,idx,val);
    else rch[h]=update(rch[h],mid+1,r,idx,val);
    //汇总该节点信息
    pushup(h);
    //将头结点返回给上级节点连接
    return h;
}
//区间和查询
ll query(int id,int l,int r,int ql,int qr) {
    //当前区间是查询区间的子集
    if(ql<=l && r<=qr) {
        return sum[id];
    }

    ll res=0;
    int mid=(l+r)>>1;
    if(ql<=mid) res+=query(lch[id],l,mid,ql,qr);
    if(qr>mid) res+=query(rch[id],mid+1,r,ql,qr);
    return res;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>q;
    for(int i=1;i<=n;i++) cin>>arr[i];

    //原始数组初始化主席树
    head[0]=build(1,n);

    for(int i=1;i<=q;i++) {
        int op;cin>>op;
        if(op==1) { //单点修改，产生新版本
            //要修改的版本
            int ver;cin>>ver;
            //要修改的数组位置
            int idx;cin>>idx;
            //修改后的值
            ll val;cin>>val;
            //从头结点head[ver]出发进行修改
            //产生新版本++version
            head[++version]=update(head[ver],1,n,idx,val);
        }
        else if(op==2) { //区间查询特定版本数组
            //要查询的版本
            int ver;cin>>ver;
            //要查询的数组区间
            int l,r;cin>>l>>r;
            //从头结点head[ver]出发进行查询
            ll ans=query(head[ver],1,n,l,r);
            cout<<ans<<'\n';
        }
    }
    return 0;
}
