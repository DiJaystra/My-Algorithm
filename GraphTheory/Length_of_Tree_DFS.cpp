/*
两次dfs求直径，输出直径长度及直径上所有的点
若有多条直径，只输出一条
注意：该方法在边权为负数时会出错
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=5e5+5; //最大点数

int n; //点数

vector<pair<int,ll>> G[MAXN]; //邻接表

int fa[MAXN]; //节点的父亲
ll dist[MAXN]; //节点到根的距离

//自定根节点，dfs计算fa数组和dist数组
void dfs(int u,int f,ll d) {
    fa[u]=f;
    dist[u]=d;
    for(auto [v,w]:G[u]) {
        if(v!=f) {
            dfs(v,u,d+w);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n-1;i++) {
        int u,v;cin>>u>>v;
        ll w;cin>>w;
        G[u].push_back({v,w});
        G[v].push_back({u,w});
    }

    //以1为根，先跑一次dfs
    dfs(1,0,0);

    //找到距离1最远的点，让它作为直径的一端
    int root=1;
    for(int i=2;i<=n;i++) {
        if(dist[i]>dist[root]) root=i;
    }

    //以这个最远点为根，重新跑一遍dfs
    dfs(root,0,0);

    //找离root最远的点，作为直径的另一端点
    int far=1;
    for(int i=2;i<=n;i++) {
        if(dist[i]>dist[far]) far=i;
    }

    //ans数组收集直径上的所有点
    vector<int> ans;
    //从far这个点根据父亲数组不断上跳
    int cur=far;
    while(cur!=0) {
        ans.push_back(cur);
        cur=fa[cur];
    }
    //得到ans数组即为直径上的所有点（从far到root）

    cout<<dist[far]<<'\n';
    for(int x:ans) cout<<x<<' ';
    cout<<'\n';
    return 0;
}
