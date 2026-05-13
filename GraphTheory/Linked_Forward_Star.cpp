#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//空间要求较苛刻时，用链式前向星
vector<int> head,nxt,to;
vector<ll> weight;

void addEdge(int id,int u,int v,ll w) {
    nxt[id]=head[u];
    to[id]=v;
    weight[id]=w;
    head[u]=id;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);

    //这里以无向有权图为例
    int n,m;cin>>n>>m; //点数，边数
    head.resize(n+1,-1); //节点的头边
    nxt.resize(2*m,-1); //边的下一条边
    to.resize(2*m,-1); //这条边指向哪个节点
    weight.resize(2*m,-1); //边的权重

    //建图
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