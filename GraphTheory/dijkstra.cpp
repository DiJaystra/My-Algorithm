#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //最大点数

int n,m,s; //点数，边数，起点
vector<vector<pair<int,ll>>> graph; //邻接表
ll dist[MAXN]; //单源最短路径长度

void dijkstra() {
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    dist[s]=0;
    pq.push({0,s});
    while(!pq.empty()) {
        auto [now,u]=pq.top();pq.pop();
        if(now > dist[u]) continue; //关键优化
        for(auto [v,w]:graph[u]) {
            ll tot=now+w;
            if(tot < dist[v]) {
                dist[v]=tot;
                pq.push({tot,v});
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m>>s;
    graph.resize(MAXN);
    fill(dist,dist+MAXN,LLONG_MAX);
    for(int i=1;i<=m;i++) {
        int u,v;ll w;cin>>u>>v>>w;
        graph[u].push_back({v,w}); //注意这里是有向图
    }

    dijkstra();
    for(int i=1;i<=n;i++) {
        cout<<dist[i]<<' ';
    }
    cout<<'\n';
    return 0;
}
