#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //最大点数

int n,m; //点数、边数
vector<vector<int>> G; //邻接表
int indeg[MAXN]; //顶点入度

int topo[MAXN]; //拓扑序
int cntt=0; //拓扑序编号分配

//判断有向图是否有环
void solve() {
    cin>>n>>m;
    for(int i=1;i<=n;i++) {
        G[i].clear();
        indeg[i]=0;
    }
    for(int i=1;i<=m;i++) {
        int u,v;cin>>u>>v;
        G[u].push_back(v); //有向图
        indeg[v]++;
    }

    //拓扑排序
    queue<int> q;
    for(int i=1;i<=n;i++) {
        //入度为0节点入队
        if(indeg[i]==0) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        int u=q.front();q.pop();
        topo[++cntt]=u;
        for(int v:G[u]) {
            //入度为0节点入队
            if(--indeg[v]==0) {
                q.push(v);
            }
        }
    }

    if(cntt==n) cout<<"YES\n";
    else cout<<"NO\n";
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    G.resize(MAXN);
    int T;cin>>T;
    while(T--) solve();
    return 0;
}