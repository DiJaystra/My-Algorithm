#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;

int n,m;
vector<vector<pair<int,ll>>> graph;
vector<ll> dist;

bool bellman(int s) {
    dist[s]=0;

    vector<bool> inque(n+1); //节点是否在队列中
    queue<int> que;
    que.push(s),inque[s]=true;

    bool have_neg=false; //是否有负环
    vector<int> cnt(n+1); //节点被几次加入队列
    cnt[s]=1;

    while(!que.empty()) {
        int cur=que.front();que.pop();
        inque[cur]=false;
        for(auto [to,val] : graph[cur]) {
            if(dist[cur]+val < dist[to]) {
                dist[to]=dist[cur]+val;
                if(!inque[to]) {
                    que.push(to);
                    inque[to]=true;
                    
                    cnt[to]++;
                    if(cnt[to]>=n) { //加入队列次数大于等于n则松弛过多，有负环
                        have_neg=true;
                        break;
                    }
                }
            }
        }
        if(have_neg) break;
    }

    return have_neg;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);

    cin>>n>>m;
    for(int i=0;i<m;i++) {
        int u,v;ll w;
        cin>>u>>v>>w;
        graph[u].push_back({v,w}); //有向图
    }
    dist.assign(n+1,LLONG_MAX);

    int s;cin>>s;
    bool flag=bellman(s);
    if(flag) {
        cout<<"-1\n";
        return 0;
    }
    
    for(int i=1;i<=n;i++) {
        cout<<dist[i]<<' ';
    }
    cout<<'\n';

    return 0;
}