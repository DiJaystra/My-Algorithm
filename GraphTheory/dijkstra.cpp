#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
using lll=__int128;

int n,m;
vector<vector<pair<int,ll>>> graph;
vector<ll> dist; //单源最短路径长度

void dijkstra(int s) {
    dist[s]=0;
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<>> pq;
    pq.push({0,s});
    while(!pq.empty()) {
        auto [now,u]=pq.top();pq.pop();
        if(now > dist[u]) continue; //关键优化
        for(auto [v,val]:graph[u]) {
            ll tot=now+val;
            if(tot<dist[v]) {
                dist[v]=tot;
                pq.push({tot,v});
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    
    int s; //起点
    cin>>n>>m>>s;
    graph.resize(n+1);
    dist.resize(n+1,LLONG_MAX);
    for(int i=0;i<m;i++) {
        int u,v,w;cin>>u>>v>>w;
        graph[u].push_back({v,w}); //注意这里是有向图
    }

    dijkstra(s);
    for(int i=1;i<=n;i++) {
        cout<<dist[i]<<' ';
    }
    cout<<'\n';
    
    return 0;
}
