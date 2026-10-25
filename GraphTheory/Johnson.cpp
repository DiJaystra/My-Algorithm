/*
SPFA预处理+n次dij求全源最短路
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=3e3+5; //最大点数
const ll INF=1e18; //距离无穷大

int n,m; //最大点数，最大边数

//邻接表
vector<pair<int,ll>> G[MAXN];

//节点最低势能
ll h[MAXN];
//节点是否在队列
bool inque[MAXN];
//节点入队次数
int times[MAXN];

ll dist[MAXN][MAXN];

//SPFA得到每个节点的最低势能，若有负环，停止
bool spfa(int s) {
    queue<int> q;
    h[s]=0;
    q.push(s);
    inque[s]=true;
    times[s]=1;

    while(!q.empty()) {
        int u=q.front();q.pop();
        inque[u]=false;
        for(auto [v,w]:G[u]) {
            if(h[u]+w<h[v]) {
                h[v]=h[u]+w;
                if(!inque[v]) {
                    q.push(v);
                    inque[v]=true;
                    if(++times[v]>=n+1) {
                        return true;
                    }
                }
            }
        }
    }

    return false;
}

//从节点s跑dijkstra单源最短路
void dijkstra(int s) {
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    dist[s][s]=0;
    pq.push({0,s});

    while(!pq.empty()) {
        auto [now,u]=pq.top();pq.pop();
        if(now>dist[s][u]) continue;

        for(auto [v,w]:G[u]) {
            ll tot=dist[s][u]+w;
            if(tot<dist[s][v]) {
                dist[s][v]=tot;
                pq.push({tot,v});
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++) {
        int u,v;cin>>u>>v;
        ll w;cin>>w;
        G[u].push_back({v,w});
    }
    //超级源点0，向所有点连一条权值为0的边
    for(int i=1;i<=n;i++) {
        G[0].push_back({i,0});
    }

    //最低势能初始化为正无穷
    for(int i=0;i<=n;i++) h[i]=INF;
    //从0开始跑SPFA
    if(spfa(0)) {
        cout<<"-1\n";
        return 0;
    }

    //将所有原图边权改为w+h[u]-h[v]
    for(int u=1;u<=n;u++) {
        for(auto &[v,w]:G[u]) {
            w=w+h[u]-h[v];
        }
    }

    //dist数组初始化为正无穷
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            dist[i][j]=INF;
        }
    }
    //从每个节点开始跑dijkstra
    for(int i=1;i<=n;i++) {
        dijkstra(i);
    }

    //还原真实最短距离
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            //能到达才需要还原
            if(dist[i][j]!=INF) {
                dist[i][j]=dist[i][j]-h[i]+h[j];
            }
        }
    }

    //输出最短距离矩阵
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            if(dist[i][j]==INF) cout<<"-1 ";
            else cout<<dist[i][j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
