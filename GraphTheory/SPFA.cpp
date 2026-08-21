#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5;

int n,m; //点数、边数
//邻接表
vector<vector<pair<int,ll>>> graph;
//距离
ll dist[MAXN];

//节点是否在队列中
bool inque[MAXN];
//节点被几次加入队列
int times[MAXN];

//起点为s，跑最短路算法
bool spfa(int s) {
    dist[s]=0;
    //将起点入队
    queue<int> que;
    que.push(s);
    inque[s]=true;
    times[s]=1;

    while(!que.empty()) {
        int u=que.front();que.pop();
        inque[u]=false;
        for(auto [v,w] : graph[u]) {
            if(dist[u]+w < dist[v]) {
                dist[v]=dist[u]+w;
                if(!inque[v]) {
                    que.push(v);
                    inque[v]=true;
                    times[v]++;
                    //加入队列次数大于等于n则松弛过多，有负环
                    if(times[v]>=n) {
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    graph.resize(MAXN);
    fill(dist,dist+MAXN,LLONG_MAX);
    for(int i=1;i<=m;i++) {
        int u,v;ll w;
        cin>>u>>v>>w;
        graph[u].push_back({v,w}); //有向图
    }

    int s;cin>>s;
    bool neg=spfa(s);
    if(neg) {
        cout<<"-1\n";
        return 0;
    }
    
    for(int i=1;i<=n;i++) {
        cout<<dist[i]<<' ';
    }
    cout<<'\n';
    return 0;
}