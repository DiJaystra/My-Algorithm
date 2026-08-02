//空间要求较苛刻时，用链式前向星
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//最大点数，最大无向边数
const int MAXN=2e5+5;
const int MAXM=2e5+5;

int n,m; //点数，边数
//点的头边，边的下一条边，边的终点
int head[MAXN],nxt[MAXM*2],to[MAXM*2];
//边的权重
ll weight[MAXM*2];
int cntg=1;

void addEdge(int u,int v,ll w) {
    nxt[++cntg]=head[u];
    to[cntg]=v;
    weight[cntg]=w;
    head[u]=cntg;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    //这里以无向有权图为例
    for(int i=0;i<m;i++) {
        int u,v;ll w;cin>>u>>v>>w;
        addEdge(u,v,w);
        addEdge(v,u,w); //无向图要双向边
    }
    //对于每个顶点，取它的边
    for(int i=1;i<=n;i++) {
        for(int e=head[i];e!=0;e=nxt[e]) {
            cout<<i<<' '<<to[e]<<' '<<weight[e]<<'\n';
        }
    }
    return 0;
}