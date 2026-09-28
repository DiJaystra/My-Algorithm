/*
给定n个变量，m个不等式，每个不等式只含两个不同的变量
求是否有解，如果有，输出任意一组特解
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=5e3+5; //最大点数

int n,m; //点数、边数

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
                    //加入队列次数大于等于n则松弛过多，有负环
                    if(times[v]>n) {
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
    for(int i=1;i<=m;i++) {
        //方程：x_v-x_u <= w
        int v,u;cin>>v>>u;
        ll w;cin>>w;
        G[u].push_back({v,w});
    }
    //图不一定连通，设置超级源点0，向所有点连一条边权为0的边
    for(int i=1;i<=n;i++) {
        G[0].push_back({i,0});
    }

    //距离数组初始化
    fill(dist,dist+MAXN,LLONG_MAX);

    bool neg=spfa(0);
    if(neg) { //有负环，无解
        cout<<"NO\n";
        return 0;
    }

    //无负环，此时距离数组就是一组解
    for(int i=1;i<=n;i++) cout<<dist[i]<<' ';
    cout<<'\n';
    return 0;
}
