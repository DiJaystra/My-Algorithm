//一个初始数组，区间修改产生新版本
//查询某版本的区间和
//这是通用方法，适用于任何线段树的可持久化
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//最大数组长度
const int MAXN=2e5+5;
//最大版本数量
const int MAXV=2e5+5;
//主席树最大节点数量
//初始线段树最多2n-1个节点
//每次修改（不考虑懒标记）最多新增2*(ceil(log_2 n)+1)=38个节点
//乘2是因为区间修改可以把任务拆到左右区间去
//当然左右区间可能又可以各自拆分成两个区间
//所以可能常数稍大（实际做题贴着内存上限开吧）
//然后考虑懒标记，懒更新下发一次产生两个节点
//所以约(2*MAXN+38*2*MAXN)个节点，如果保守还要再大一些
const int MAXT=MAXN*78;

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
//lazy[i]：节点i的懒更新标记
ll lazy[MAXT];
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
    lazy[h]=lazy[id];
    return h;
}
//汇总节点信息
void pushup(int id) {
    sum[id]=sum[lch[id]]+sum[rch[id]];
}
//给节点id接收lz这个标记
void mark(int id,int len,ll lz) {
    sum[id]+=lz*len;
    lazy[id]+=lz;
}
//懒更新下发
void pushdown(int id,int l,int r) {
    if(lazy[id]!=0) {
        ll lz=lazy[id];
        int mid=(l+r)>>1;
        //左儿子新建并接收懒更新
        lch[id]=clone(lch[id]);
        mark(lch[id],mid-l+1,lz);
        //右儿子新建并接收懒更新
        rch[id]=clone(rch[id]);
        mark(rch[id],r-mid,lz);
        //当前节点清空懒标记
        lazy[id]=0;
    }
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
//区间修改操作
int range(int id,int l,int r,int ql,int qr,ll val) {
    //拷贝原节点信息
    int h=clone(id);
    //当前区间是查询区间的子集
    if(ql<=l&&r<=qr) {
        //修改并挂上懒标记
        mark(h,r-l+1,val);
        return h;
    }

    int mid=(l+r)>>1;
    pushdown(h,l,r); //懒标记下发
    //去往要修改的节点
    if(ql<=mid) lch[h]=range(lch[h],l,mid,ql,qr,val);
    if(qr>mid) rch[h]=range(rch[h],mid+1,r,ql,qr,val);
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
    pushdown(id,l,r); //懒标记下发
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
        if(op==1) { //区间修改，产生新版本
            //要修改的版本
            int ver;cin>>ver;
            //要修改的数组区间
            int l,r;cin>>l>>r;
            //修改的变化值
            ll val;cin>>val;
            //从头结点head[ver]出发进行修改
            //产生新版本++version
            head[++version]=range(head[ver],1,n,l,r,val);
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
