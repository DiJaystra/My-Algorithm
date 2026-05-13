#include<bits/stdc++.h>
using namespace std;
using ll=long long;

int n,m,root;
vector<vector<int>> G;
vector<int> fa,dep,siz,son,top,dfn,seg;
int cntd=0; //dfn序号分配

//设置father,depth,size,heavy_son
void dfs1(int u,int f) {
    fa[u]=f;
    dep[u]=dep[f]+1;
    siz[u]=1;

    for(int v : G[u]) {
        if(v!=f) dfs1(v,u);
    }

    for(int v : G[u]) {
        if(v!=f) {
            siz[u]+=siz[v];
            if(son[u]==-1 || siz[son[u]] < siz[v]) son[u]=v;
        }
    }
}
//设置top,dfn,seg
void dfs2(int u,int t) {
    top[u]=t;
    dfn[u]=++cntd;
    seg[cntd]=u;
    if(son[u]==-1) return;
    dfs2(son[u],t); //先遍历重儿子
    for(int v : G[u]) {
        if(v!=fa[u] && v!=son[u]) {
            dfs2(v,v); //轻儿子重新分配头结点
        }
    }
}
//求最近公共祖先(实际上这个功能不需要dfn和seg)
int lca(int a,int b) {
    while(top[a]!=top[b]) {
        if(dep[top[a]] <= dep[top[b]]) {
            b=fa[top[b]];
        } else {
            a=fa[top[a]];
        }
    }
    return dep[a]>=dep[b] ? b : a;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);

    cin>>n>>m>>root;
    G.assign(n+1,vector<int>(0));
    fa.assign(n+1,-1);
    dep.assign(n+1,0);
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

    while(m--) {
        int a,b;cin>>a>>b;
        cout<<lca(a,b)<<'\n';
    }

    return 0;
}