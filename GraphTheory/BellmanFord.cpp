#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5;
const int MAXM=2e5+5;

int n,m; //点数、边数
//邻接表
vector<vector<pair<int,ll>>> graph;
//距离
ll dist[MAXN];

//边结构体
struct edge {
    int u,v;
    ll w;
};
edge E[MAXM]; //把所有边记下来

//起点为s，跑最短路算法，返回是否有负环
//注意，只能判断从s出发是否能到达负环
//若需判断整张图有无负环，要用虚拟源点作为出发点
//虚拟源点连接原图中所有实际点
//复杂度O(nm)
bool bellman(int s) {
    dist[s]=0;
    int cnt=0; //松弛轮数
    while(1) {
        //是否有更短距离的更新
        bool update=false;
        //每轮遍历每条边
        for(int i=1;i<=m;i++) {
            auto [u,v,w]=E[i];
            //到v距离更短
            if(dist[u]!=LLONG_MAX&&dist[u]+w<dist[v]) {
                dist[v]=dist[u]+w;
                update=true;
            }
        }
        //没有松弛操作，则所有最短路都已经找到
        if(!update) break;
        //否则松弛次数+1
        cnt++;
        //最多松弛n-1次，超过则有负环
        if(cnt>=n) return true;
    }
    //无负环
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
        E[i]={u,v,w};
    }

    int s;cin>>s;
    bool neg=bellman(s);
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