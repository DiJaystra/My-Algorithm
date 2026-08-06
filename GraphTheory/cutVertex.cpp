#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//最大点数，最大无向边数
const int MAXN=2e4+5;
const int MAXM=1e5+5;

int n,m; //点数，边数

//点的头边，边的下一条边，边的终点
int head[MAXN],nxt[MAXM<<1],to[MAXM<<1];
int cntg=1; //边的编号分配

//节点的dfn编号，low值
int dfn[MAXN],low[MAXN];
int cntd=0; //dfn编号分配

//点i是否为割点
bool cutVertex[MAXN];

void addEdge(int u,int v) {
    nxt[++cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg;
}

//当前来到点u，它是否是当前连通区根节点
void tarjan(int u,bool root) {
    dfn[u]=low[u]=++cntd; //dfn序分配
    int son=0; //树边儿子数量
    //遍历节点的所有出边
    for(int e=head[u];e!=0;e=nxt[e]) {
        int v=to[e];
        if(dfn[v]==0) { //树边
            son++; //树边儿子数量++
            tarjan(v,false);
            low[u]=min(low[u],low[v]);
            //判断是否为割点
            //low[v]>=dfn[u]这个条件在u为根时一定成立
            if(low[v]>=dfn[u]) {
                if(!root || son>=2) {
                    cutVertex[u]=true;
                }
            }
        }
        else if(dfn[v]<dfn[u]) { //回边
            low[u]=min(low[u],dfn[v]);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++) {
        int u,v;cin>>u>>v;
        addEdge(u,v);
        addEdge(v,u);
    }

    //图不一定全连通，每个点都考察是否来到
    //没来过就跑tarjan，且它是根节点
    for(int u=1;u<=n;u++) {
        if(dfn[u]==0) tarjan(u,true);
    }

    //输出割点数量及割点编号
    int ans=0;
    for(int i=1;i<=n;i++) {
        if(cutVertex[i]) ans++;
    }
    cout<<ans<<'\n';
    for(int i=1;i<=n;i++) {
        if(cutVertex[i]) cout<<i<<' ';
    }
    cout<<'\n';
    return 0;
}
