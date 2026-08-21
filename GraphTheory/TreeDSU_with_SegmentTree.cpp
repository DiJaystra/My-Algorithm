#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //最大节点数量

int n,root,Q; //节点个数，指定根节点，询问个数
ll MOD; //取模数值
vector<vector<int>> G; //邻接表
ll arr[MAXN]; //节点的值

int fa[MAXN]; //节点父亲
int dep[MAXN]; //节点深度
int siz[MAXN]; //子树大小
int son[MAXN]; //节点的重儿子编号
int top[MAXN]; //节点所在重链的头节点编号
int dfn[MAXN]; //节点的dfn序
int seg[MAXN]; //dfn序号为i的节点
int cntd=0; //dfn序号分配

ll tree[MAXN<<2],lazy[MAXN<<2]; //线段树基本信息

//多例子初始化
void prepare() {
    for(int i=1;i<=n;i++) {
        G[i].clear();
        son[i]=0;
    }
    cntd=0;
}

//设置father,depth,size,heavy_son
void dfs1(int u,int f) { //当前节点，当前节点的父亲节点
    fa[u]=f;
    dep[u]=dep[f]+1;
    siz[u]=1; //子树大小初始化为自己一个，等会加上儿子的子树大小
    for(int v : G[u]) {
        if(v!=f) dfs1(v,u);
    }
    for(int v : G[u]) {
        if(v!=f) {
            siz[u]+=siz[v];
            if(son[u]==0 || siz[son[u]] < siz[v]) son[u]=v; //更新重儿子
        }
    }
}
//设置top,dfn,seg
void dfs2(int u,int t) { //当前节点，当前节点所在重链的头结点
    top[u]=t;
    dfn[u]=++cntd;
    seg[cntd]=u;
    if(son[u]==0) return;
    dfs2(son[u],t); //先遍历重儿子
    for(int v : G[u]) {
        if(v!=fa[u] && v!=son[u]) { //遍历轻儿子
            dfs2(v,v); //轻儿子重新分配头结点
        }
    }
}

//建线段树
void build(int id,int l,int r) {
    if(l==r) {
        tree[id]=arr[seg[l]]%MOD;
        lazy[id]=0;
        return;
    }
    int mid=(l+r)>>1;
    build(id<<1,l,mid);
    build(id<<1|1,mid+1,r);
    tree[id]=(tree[id<<1]+tree[id<<1|1])%MOD;
}
//懒标记下发
void pushdown(int id,int l,int r) {
    if(lazy[id]==0) return;
    ll lz=lazy[id];
    int mid=(l+r)>>1;
    tree[id<<1]=(tree[id<<1]+(mid-l+1)*lz%MOD)%MOD;
    tree[id<<1|1]=(tree[id<<1|1]+(r-mid)*lz%MOD)%MOD;
    lazy[id<<1]=(lazy[id<<1]+lz)%MOD;
    lazy[id<<1|1]=(lazy[id<<1|1]+lz)%MOD;
    lazy[id]=0;
}
//线段树区间修改
void updateRange(int id,ll l,ll r,int ql,int qr,ll val) {
    if(ql <= l && r <= qr) {
        tree[id]=(tree[id]+(r-l+1)*val%MOD)%MOD;
        lazy[id]=(lazy[id]+val)%MOD;
        return;
    }
    int mid=(l+r)>>1;
    pushdown(id,l,r);
    if(ql <= mid) updateRange(id<<1,l,mid,ql,qr,val);
    if(qr > mid) updateRange(id<<1|1,mid+1,r,ql,qr,val);
    tree[id]=(tree[id<<1]+tree[id<<1|1])%MOD;
}
//线段树区间查询
ll query(int id,int l,int r,int ql,int qr) {
    if(ql <= l && r <= qr) {
        return tree[id];
    }
    int mid=(l+r)>>1;
    pushdown(id,l,r);
    ll res=0;
    if(ql <= mid) res=(res+query(id<<1,l,mid,ql,qr))%MOD;
    if(qr > mid) res=(res+query(id<<1|1,mid+1,r,ql,qr))%MOD;
    return res;
}
//x到y的路径上，每个点的值+=val
void pathAdd(int x,int y,ll val) {
    while(top[x]!=top[y]) {
        if(dep[top[x]]<=dep[top[y]]) {
            updateRange(1,1,n,dfn[top[y]],dfn[y],val);
            y=fa[top[y]];
        }
        else {
            updateRange(1,1,n,dfn[top[x]],dfn[x],val);
            x=fa[top[x]];
        }
    }
    updateRange(1,1,n,min(dfn[x],dfn[y]),max(dfn[x],dfn[y]),val);
}
//x这棵子树，每个节点的值+=val
void subtreeAdd(int x,ll val) {
    updateRange(1,1,n,dfn[x],dfn[x]+siz[x]-1,val);
}
//查询x到y路径上，所有点的值之和
ll pathQuery(int x,int y) {
    ll res=0;
    while(top[x]!=top[y]) {
        if(dep[top[x]]<=dep[top[y]]) {
            res=(res+query(1,1,n,dfn[top[y]],dfn[y]))%MOD;
            y=fa[top[y]];
        }
        else {
            res=(res+query(1,1,n,dfn[top[x]],dfn[x]))%MOD;
            x=fa[top[x]];
        }
    }
    res=(res+query(1,1,n,min(dfn[x],dfn[y]),max(dfn[x],dfn[y])))%MOD;
    return res;
}
//查询x这棵子树，所有点的值之和
ll subtreeQuery(int x) {
    return query(1,1,n,dfn[x],dfn[x]+siz[x]-1);
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    G.resize(MAXN);
    cin>>n>>Q>>root>>MOD;
    prepare();
    for(int i=1;i<=n;i++) cin>>arr[i];
    for(int i=1;i<=n-1;i++) {
        int u,v;cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    
    dfs1(root,0);
    dfs2(root,root);
    build(1,1,n);

    while(Q--) {
        int op;cin>>op;
        if(op==1) { //路径修改
            int x,y;ll val;cin>>x>>y>>val;
            pathAdd(x,y,val);
        }
        else if(op==2) { //路径查询
            int x,y;cin>>x>>y;
            cout<<pathQuery(x,y)<<'\n';
        }
        else if(op==3) { //子树修改
            int x;ll val;cin>>x>>val;
            subtreeAdd(x,val);
        }
        else { //子树查询
            int x;cin>>x;
            cout<<subtreeQuery(x)<<'\n';
        }
    }
    return 0;
}