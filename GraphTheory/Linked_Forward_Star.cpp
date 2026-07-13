//空间要求较苛刻时，用链式前向星
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//最大点数，最大边数
const int MAXN=2e5+5;
const int MAXM=2e5+5;

int n,m; //点数，边数
//点的头边，边的下一条边，边的终点
int head[MAXN],nxt[MAXM*2],to[MAXM*2];
//边的权重
ll weight[MAXM*2];

void addEdge(int id,int u,int v,ll w) {
    nxt[id]=head[u];
    to[id]=v;
    weight[id]=w;
    head[u]=id;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) head[i]=-1;
    //这里以无向有权图为例
    for(int i=0;i<m;i++) {
        int u,v;ll w;cin>>u>>v>>w;
        addEdge(2*i,u,v,w);
        addEdge(2*i+1,v,u,w); //无向图要双向边
    }
    //对于每个顶点，取它的边
    for(int i=1;i<=n;i++) {
        for(int ei=head[i];ei!=-1;ei=nxt[ei]) {
            cout<<i<<' '<<to[ei]<<' '<<weight[ei]<<'\n';
        }
    }
    return 0;
}