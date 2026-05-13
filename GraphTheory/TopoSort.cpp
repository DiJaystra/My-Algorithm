#include <bits/stdc++.h>
using namespace std;
using ll=long long;

void solve() {
    int n,m;cin>>n>>m;
    vector<vector<int>> graph(n+1);
    vector<int> indeg(n+1);
    for(int i=0;i<m;i++) {
        int u,v;cin>>u>>v;
        graph[u].push_back(v);
        indeg[v]++;
    }

    queue<int> q;
    vector<int> topo;
    for(int i=1;i<=n;i++) {
        if(indeg[i]==0) {
            q.push(i);
        }
    }

    while(!q.empty()) {
        int u=q.front();q.pop();
        topo.push_back(u);
        for(int v:graph[u]) {
            indeg[v]--;
            if(indeg[v]==0) {
                q.push(v);
            }
        }
    }

    if(topo.size()==n) {
        cout<<"YES\n";
    }
    else {
        cout<<"NO\n";
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);

    int t;cin>>t;
    while(t--) solve();

    return 0;
}