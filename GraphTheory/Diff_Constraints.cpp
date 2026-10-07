/*
给定n个变量，m个不等式，每个不等式只含两个不同的变量
同时给定k个确定值的变量
求是否有解，如果有，输出任意一组特解
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=5e3+5; //最大点数

int n,m; //点数、边数
int k; //有几个变量已知具体值

vector<pair<int,ll>> G[MAXN]; //邻接表

ll dist[MAXN]; //最短距离数组

bool inque[MAXN]; //节点是否在队列中
int times[MAXN]; //节点入队几次

//SPFA算法求最短路同时判断负环
bool spfa(int s) {
    queue<int> q;
    //将起点入队
    dist[s]=0;
    q.push(s);
    inque[s]=true;
    times[s]=1;

    while(!q.empty()) {
        int u=q.front();q.pop();
        inque[u]=false;
        for(auto [v,w]:G[u]) {
            if(dist[u]+w<dist[v]) {
                dist[v]=dist[u]+w;
                if(!inque[v]) {
                    q.push(v);
                    inque[v]=true;
                    times[v]++;
                    //加入队列次数大于n+1则松弛过多，有负环
                    if(times[v]>=n+2) {
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
    cin>>n>>m>>k;
    //读入不等式方程
    for(int i=1;i<=m;i++) {
        //方程：x_v-x_u <= w
        int v,u;cin>>v>>u;
        ll w;cin>>w;
        G[u].push_back({v,w});
    }
    //读入已确定变量的值
    //用限制超级源点来限制已确定的变量的值
    for(int i=1;i<=k;i++) {
        int u;cin>>u;
        ll w;cin>>w;
        G[n+1].push_back({u,w});
        G[u].push_back({n+1,-w});
    }
    //图不一定连通，设置连通超级源点0，向所有点连一条边权为0的边
    for(int i=1;i<=n+1;i++) {
        G[0].push_back({i,0});
    }

    //距离数组初始化
    fill(dist,dist+MAXN,LLONG_MAX);

    bool neg=spfa(0);
    if(neg) { //有负环，无解
        cout<<"NO\n";
        return 0;
    }

    //无负环，将距离数组还原为解（将限制超级源点n+1的距离归零）
    for(int i=1;i<=n;i++) {
        dist[i]-=dist[n+1];
    }
    dist[n+1]=0;
    for(int i=1;i<=n;i++) cout<<dist[i]<<' ';
    cout<<'\n';
    return 0;
}
