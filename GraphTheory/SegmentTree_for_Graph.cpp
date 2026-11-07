/*
线段树优化建图
解决批量连边问题，包括：
1、单点向区间连边
2、区间向单点连边
3、区间向区间连边

注意：
1、此模板只连有向边，若连无向边，反着再调用一次函数
2、出树入树叶子节点共用，编号即为原图节点编号
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=5e5+5; //最大点数
const int MAXM=1e5+5; //最多批量连边次数
//最大总点数
//包括出树和入树这两棵线段树的节点总数2*4*n
//以及区间向区间连边时产生的超级源点数2*m
//如果是无向边，MAXM应该*4
const int MAXT=MAXN*8+MAXM*2;
//因为动态开点，所以其实MAXT=MAXN*3+MAXM*2就够

int n,m; //点数、批量连边次数

//邻接表，包括虚拟点
//{终点，边权}
vector<pair<int,ll>> G[MAXT];

//线段树左孩子编号，有孩子编号
int lch[MAXT],rch[MAXT];
//出树头节点编号，入树头节点编号
int outRoot=0,inRoot=0;
//节点编号分配
int cntt=0;

//构建出树
int buildOut(int l,int r) {
    //叶子节点，点的编号就是原图编号
    if(l==r) {
        return l;
    }

    //当前非叶节点，分配新编号
    int root=++cntt;

    //构建左右孩子，并连接
    int mid=(l+r)>>1;
    lch[root]=buildOut(l,mid);
    rch[root]=buildOut(mid+1,r);

    //出树要求子区间指向父区间
    G[lch[root]].push_back({root,0});
    G[rch[root]].push_back({root,0});

    //将当前节点返回给上级连接
    return root;
}

//构建入树
int buildIn(int l,int r) {
    //叶子节点，点的编号就是原图编号
    if(l==r) {
        return l;
    }

    //当前非叶节点，分配新编号
    int root=++cntt;

    //构建左右孩子，并连接
    int mid=(l+r)>>1;
    lch[root]=buildIn(l,mid);
    rch[root]=buildIn(mid+1,r);

    //入树要求父区间指向子区间
    G[root].push_back({lch[root],0});
    G[root].push_back({rch[root],0});

    //将当前节点返回给上级连接
    return root;
}

//单点向区间连边
//参数：当前线段树节点、当前区间左、右边界、连边单点、连边区间、连边权值
void x_range(int id,int l,int r,int x,int ql,int qr,ll w) {
    //区间全包
    if(ql<=l && r<=qr) {
        //叶子单点向入树区间点连一条权值w的有向边
        G[x].push_back({id,w});
        return;
    }
    //未全包区间，向更小区间拆分
    int mid=(l+r)>>1;
    if(ql<=mid) x_range(lch[id],l,mid,x,ql,qr,w);
    if(qr>mid) x_range(rch[id],mid+1,r,x,ql,qr,w);
}

//区间向单点连边
//参数：当前线段树节点、当前区间左、右边界、连边区间、连边单点、连边权值
void range_x(int id,int l,int r,int ql,int qr,int x,ll w) {
    //区间全包
    if(ql<=l && r<=qr) {
        //出树区间点向叶子单点连一条权值w的有向边
        G[id].push_back({x,w});
        return;
    }
    //未全包区间，向更小区间拆分
    int mid=(l+r)>>1;
    if(ql<=mid) range_x(lch[id],l,mid,ql,qr,x,w);
    if(qr>mid) range_x(rch[id],mid+1,r,ql,qr,x,w);
}

//区间向区间连边，依靠上面两个函数实现
//参数：出树区间outl到outr，入树区间inl到inr
void range_range(int outl,int outr,int inl,int inr,ll w) {
    //虚拟源点x：出树拆分的区间都向x连一条权值为0的边
    int x=++cntt;
    range_x(outRoot,1,n,outl,outr,x,0);
    //虚拟源点y：x向入树拆分的区间都连一条权值为0的边
    int y=++cntt;
    x_range(inRoot,1,n,y,inl,inr,0);
    //最后，x->y连一条权值为w的边
    G[x].push_back({y,w});
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;

    //叶子已经占用编号1~n，从n+1开始编号
    cntt=n;
    //构建出树入树，且记录出入树根节点
    outRoot=buildOut(1,n);
    inRoot=buildIn(1,n);

    for(int i=1;i<=m;i++) {
        int op;cin>>op;
        if(op==1) { //单点向单点连边
            int u,v;cin>>u>>v;
            ll w;cin>>w;
            G[u].push_back({v,w});
            //若无向边，添加：
            //G[v].push_back({u,w});
        }
        else if(op==2) { //单点向区间连边
            int u,l,r;cin>>u>>l>>r;
            ll w;cin>>w;
            x_range(inRoot,1,n,u,l,r,w);
            //若无向边，添加：
            //range_x(outRoot,1,n,l,r,u,w);
        }
        else if(op==3) { //区间向单点连边
            int l,r,v;cin>>l>>r>>v;
            ll w;cin>>w;
            range_x(outRoot,1,n,l,r,v,w);
            //若无向边，添加：
            //x_range(inRoot,1,n,v,l,r,w);
        }
        else if(op==4) { //区间向区间连边
            int l1,r1,l2,r2;cin>>l1>>r1>>l2>>r2;
            ll w;cin>>w;
            range_range(l1,r1,l2,r2,w);
            //若无向边，添加：
            //range_range(l2,r2,l1,r1,w);
        }
    }
    return 0;
}
