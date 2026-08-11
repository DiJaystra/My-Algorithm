#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=205; //最大点数

int n,m; //点数，边数
ll dist[MAXN][MAXN]; //最短距离数组

void floyd() {
    for(int k=1;k<=n;k++) { //枚举中转点
        for(int i=1;i<=n;i++) { //枚举起点
            for(int j=1;j<=n;j++) { //枚举终点
                if(dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX) {
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                }
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    fill(&dist[0][0],&dist[0][0]+MAXN*MAXN,LLONG_MAX);
    for(int i=1;i<=n;i++) dist[i][i]=0;

    for(int i=1;i<=m;i++) {
        int u,v;cin>>u>>v;
        ll w;cin>>w;
        //支持重边与自环
        dist[u][v]=min(dist[u][v],w);
        dist[v][u]=min(dist[v][u],w);
    }

    floyd(); //1-index 传n+1
    return 0;
}