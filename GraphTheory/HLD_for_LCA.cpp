#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //最大节点数量

int n,q,root; //节点数，查询数，指定根节点
vector<vector<int>> G; //邻接表
int fa[MAXN]; //节点父亲
int dep[MAXN]; //节点深度
int siz[MAXN]; //子树大小
int son[MAXN]; //节点的重儿子编号
int top[MAXN]; //节点所在重链的头节点编号
int dfn[MAXN]; //节点的dfn序
int seg[MAXN]; //dfn序号为i的节点
int cntd=0; //dfn序号分配

//多例子初始化
void prepare() {
    for(int i=1;i<=n;i++) {
        G[i].clear();
        son[i]=0;
    }
    cntd=0;
}

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
            if(son[u]==0 || siz[son[u]] < siz[v]) son[u]=v;
        }
    }
}
//设置top,dfn,seg
void dfs2(int u,int t) {
    top[u]=t;
    dfn[u]=++cntd;
    seg[cntd]=u;
    if(son[u]==0) return;
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
        }
        else {
            a=fa[top[a]];
        }
    }
    return dep[a]>=dep[b] ? b : a;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    G.resize(MAXN);
    cin>>n>>q>>root;
    prepare();
    for(int i=0;i<n-1;i++) {
        int u,v;cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs1(root,0);
    dfs2(root,root);

    while(q--) {
        int x,y;cin>>x>>y;
        cout<<lca(x,y)<<'\n';
    }
    return 0;
}