#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int n,root; //节点个数，指定根节点
vector<vector<int>> G; //邻接表
vector<int> fa,dep,siz,son,top,dfn,seg;
int cntd=0; //dfn序号分配

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
            if(son[u]==-1 || siz[son[u]] < siz[v]) son[u]=v; //更新重儿子
        }
    }
}
//设置top,dfn,seg
void dfs2(int u,int t) { //当前节点，当前节点所在重链的头结点
    top[u]=t;
    dfn[u]=++cntd;
    seg[cntd]=u;
    if(son[u]==-1) return;
    dfs2(son[u],t); //先遍历重儿子
    for(int v : G[u]) {
        if(v!=fa[u] && v!=son[u]) { //遍历轻儿子
            dfs2(v,v); //轻儿子重新分配头结点
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);

    cin>>n>>root;
    G.assign(n+1,vector<int>(0));
    fa.assign(n+1,-1);
    dep.assign(n+1,0); //默认原始节点0在深度0处
    siz.assign(n+1,-1);
    son.assign(n+1,-1);
    top.assign(n+1,-1);
    dfn.assign(n+1,-1);
    seg.assign(n+1,-1);

    for(int i=0;i<n-1;i++) {
        int u,v;cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs1(root,0);
    dfs2(root,root);

    return 0;
}