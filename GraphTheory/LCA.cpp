#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
using lll=__int128;

const int LOG=20; //2^20>≈1e6

int n;
vector<vector<pair<int,int>>> graph;
vector<int> dep; //节点深度
vector<vector<int>> up; //跳跃父亲数组

//dfs求节点在树上的深度
void dfs(int u,int deep,vector<bool> &visited) {
    visited[u]=true;
    dep[u]=deep;
    for(auto [v,id] : graph[u]) {
        if(!visited[v]) {
            up[v][0]=u; //不需要倍增数组则去掉该行
            dfs(v,deep+1,visited);
        }
    }
}

//初处理跳跃父亲数组
void intialUp() {
    for(int i=1;i<LOG;i++) {
        for(int u=1;u<=n;u++) {
            up[u][i]=up[up[u][i-1]][i-1];
        }
    }
}

//将两节点带到同一深度
void toSame(int &x,int y) {
    int diff=dep[x]-dep[y];
    for(int i=LOG-1;i>=0;i--) {
        if(diff & (1<<i)) {
            x=up[x][i]; //x传参需要带引用的原因
        }
    }
}

//寻找两节点的最近公共祖先
int lca(int x,int y) {
    if(dep[x]<dep[y]) swap(x,y);
    toSame(x,y);

    if(x==y) return x;

    for(int i=LOG-1;i>=0;i--) {
        if(up[x][i] != up[y][i]) {
            x=up[x][i];
            y=up[y][i];
        }
    }
    return up[x][0];
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    
    cin>>n;
    //graph.resize(n+1); 单测试点多例子的初始化用下面这种
    graph=decltype(graph)(n+1);
    for(int i=0;i<n-1;i++) {
        int u,v;cin>>u>>v;
        graph[u].push_back({v,i});
        graph[v].push_back({u,i});
    }

    //初始化工作：求节点深度->求倍增数组

    //dep.resize(n+1);
    dep=decltype(dep)(n+1);
    //up.resize(n+1,vector<int> (20,0));
    up=decltype(up)(n+1,vector<int> (20,0));
    vector<bool> visited(n+1,false);
    dfs(1,1,visited);
    intialUp();

    lca(8,3); //调用方法
    
    return 0;
}
