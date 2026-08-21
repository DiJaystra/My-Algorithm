#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //最大点数
const int LOG=20; //2^20>≈1e6

int n; //点数
vector<vector<int>> graph; //邻接表
int dep[MAXN]; //节点深度
int jump[MAXN][LOG]; //跳跃父亲数组

//dfs求节点在树上的深度
void dfs(int u,int f) {
    dep[u]=dep[f]+1;
    jump[u][0]=f;
    for(int v : graph[u]) {
        if(v!=f) {
            dfs(v,u);
        }
    }
}

//初处理跳跃父亲数组
void intialJump() {
    for(int j=1;j<LOG;j++) {
        for(int i=1;i<=n;i++) {
            jump[i][j]=jump[jump[i][j-1]][j-1];
        }
    }
}

//将两节点带到同一深度
void toSame(int &x,int y) {
    int diff=dep[x]-dep[y];
    for(int i=LOG-1;i>=0;i--) {
        if((diff>>i)&1) {
            x=jump[x][i]; //x传参需要带引用的原因
        }
    }
}

//寻找两节点的最近公共祖先
int lca(int x,int y) {
    if(dep[x]<dep[y]) swap(x,y);
    toSame(x,y);

    if(x==y) return x;

    for(int i=LOG-1;i>=0;i--) {
        if(jump[x][i] != jump[y][i]) {
            x=jump[x][i];
            y=jump[y][i];
        }
    }
    return jump[x][0];
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    graph.resize(MAXN);
    for(int i=1;i<=n-1;i++) {
        int u,v;cin>>u>>v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    //初始化工作：求节点深度->求倍增数组
    dfs(1,0);
    intialJump();

    int q;cin>>q;
    while(q--) {
        int x,y;cin>>x>>y;
        cout<<lca(x,y)<<'\n';
    }
    return 0;
}
