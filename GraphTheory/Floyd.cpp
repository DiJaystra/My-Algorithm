#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
using lll=__int128;

void floyd(vector<vector<ll>> &dist,int n) {
    for(int k=0;k<n;k++) {
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                if(dist[i][k] != LLONG_MAX && dist[k][j] != LLONG_MAX) {
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
                }
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);

    int n,m;cin>>n>>m;
    vector<vector<ll>> dist(n+1,vector<ll> (n+1,LLONG_MAX)); //最短距离数组
    for(int i=1;i<=n;i++) dist[i][i]=0;

    for(int i=0;i<m;i++) {
        int u,v;cin>>u>>v;
        ll w;cin>>w;
        //支持重边与自环
        dist[u][v]=min(dist[u][v],w);
        dist[v][u]=min(dist[v][u],w);
    }

    floyd(dist,n+1); //1-index 传n+1

    return 0;
}