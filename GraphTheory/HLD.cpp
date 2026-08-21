#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //最大节点数量

int n,root; //节点个数，指定根节点
vector<vector<int>> G; //邻接表
int fa[MAXN]; //节点父亲
int dep[MAXN]; //节点深度
int siz[MAXN]; //子树大小
int son[MAXN]; //节点的重儿子编号
int top[MAXN]; //节点所在重链的头节点编号
int dfn[MAXN]; //节点的dfn序
int seg[MAXN]; //dfn序号为i的节点
int cntd=0; //dfn序号分配

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

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    G.resize(MAXN);
    cin>>n>>root;
    prepare();
    for(int i=0;i<n-1;i++) {
        int u,v;cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs1(root,0);
    dfs2(root,root);
    return 0;
}