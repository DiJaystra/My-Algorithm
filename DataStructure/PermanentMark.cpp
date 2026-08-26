//一个初始数组，区间修改产生新版本
//查询某版本的区间和
//用标记永久化的方式实现，可以节省空间
//这个方法不需要懒标记的下发，省去了懒标记下发产生的新节点
//标记永久化不意味着标记永远不变
//而是标记不会上传也不会下发
//然而这个方法适用范围较窄
//只适用于区间和这种可叠加的操作类型
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//最长数组长度
const int MAXN=2e5+5;
//最大版本数量
const int MAXV=2e5+5;
//主席树最大节点数量
//初始线段树最多2n-1个节点
//每次修改大概新增2*(ceil(log_2 n)+1)=38个节点
//乘2是因为区间修改可以把任务拆到左右区间去
//当然左右区间可能又可以各自拆分成两个区间
//所以可能常数稍大（实际做题贴着内存上限开吧）
//所以约(2*MAXN+38*MAXN)个节点，如果保守还要再大一些
const int MAXT=MAXN*40;

//数组长度，查询数量
int n,q;

//原数组
ll arr[MAXN];
//head[i]：版本号i的头节点
int head[MAXV];
//节点i的左儿子和右儿子节点编号
int lch[MAXT],rch[MAXT];
//不是真实的累加和，而是之前的任务中
//不考虑上方范围拦截的任务，只考虑来到当前及往下走的任务
//累加和变成了什么
ll sum[MAXT];
//不是懒处理标记，只是标记被拦截的任务
ll add[MAXT];
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
    add[h]=add[id];
    return h;
}
//汇总节点信息（仅在build函数用到）
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
        //在build初始化add
        add[h]=0;
        return h;
    }
    //非叶节点
    int mid=(l+r)>>1;
    //左右孩子构建
    lch[h]=build(l,mid);
    rch[h]=build(mid+1,r);
    //在build初始化add
    add[h]=0;
    //汇总该节点信息
    pushup(h);
    //将头结点返回给上级节点连接
    return h;
}
//区间修改操作
int range(int id,int l,int r,int ql,int qr,ll val) {
    //求当前区间与目标区间的交集[x,y]
    int x=max(l,ql),y=min(r,qr);
    //拷贝原节点信息
    int h=clone(id);
    //给当前节点提前pushup
    sum[h]+=val*(y-x+1);
    //当前区间是目标区间的子集
    if(ql<=l&&r<=qr) {
        //挂上标签
        add[h]+=val;
        return h;
    }

    int mid=(l+r)>>1;
    //无pushdown
    //去往要修改的节点
    if(ql<=mid) lch[h]=range(lch[h],l,mid,ql,qr,val);
    if(qr>mid) rch[h]=range(rch[h],mid+1,r,ql,qr,val);
    //不pushup
    //将头结点返回给上级节点连接
    return h;
}
//区间和查询。hist：从头节点到当前，带过来的标记之和
ll query(int id,int l,int r,int ql,int qr,ll hist) {
    //当前区间是目标区间的子集
    if(ql<=l&&r<=qr) {
        //从根节点到这里带过来的标记和hist
        //其贡献为hist*区间长度
        //区间自己的sum也参与
        return hist*(r-l+1)+sum[id];
    }

    ll res=0;
    int mid=(l+r)>>1;
    //无pushdown
    if(ql<=mid) res+=query(lch[id],l,mid,ql,qr,hist+add[id]);
    if(qr>mid) res+=query(rch[id],mid+1,r,ql,qr,hist+add[id]);
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
            ll ans=query(head[ver],1,n,l,r,0);
            cout<<ans<<'\n';
        }
    }
    return 0;
}
