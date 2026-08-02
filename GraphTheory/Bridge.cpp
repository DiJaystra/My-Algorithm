#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//最大点数，最大无向边数
const int MAXN=5e5+5;
const int MAXM=2e6+5;

int n,m; //点数，边数

//点的头边，边的下一条边，边的终点
int head[MAXN],nxt[MAXM<<1],to[MAXM<<1];
int cntg=1; //边的编号分配

//节点的dfn编号，low值
int dfn[MAXN],low[MAXN];
int cntd=0; //dfn编号分配

//边i是否为割边（桥）
bool cutEdge[MAXM];

void addEdge(int u,int v) {
    nxt[++cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg;
}

void tarjan(int u,int preEdge) {
    dfn[u]=low[u]=++cntd; //dfn序分配
    //遍历节点的所有出边
    for(int e=head[u];e!=0;e=nxt[e]) {
        //不能与来时的边是同一条无向边
        if(e==(preEdge^1)) continue;

        int v=to[e];
        //树边
        if(dfn[v]==0) {
            tarjan(v,e);
            low[u]=min(low[u],low[v]);
            //桥：v子树无法通过回边来到u上方
            if(low[v]>dfn[u]) {
                cutEdge[e>>1]=true;
            }
        }
        //回边
        else if(dfn[v]<dfn[u]) {
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
    //没来过就跑tarjan
    for(int u=1;u<=n;u++) {
        if(dfn[u]==0) tarjan(u,0);
    }

    //输出割边数量以及所有割边对应无向图编号
    int ans=0;
    for(int i=1;i<=m;i++) {
        if(cutEdge[i]) ans++;
    }
    cout<<ans<<'\n';
    for(int i=1;i<=m;i++) {
        if(cutEdge[i]) cout<<i<<' ';
    }
    cout<<'\n';
    return 0;
}
