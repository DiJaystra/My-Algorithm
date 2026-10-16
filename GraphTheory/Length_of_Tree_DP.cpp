/*
树型dp求直径长度，仅输出直径长度
该方法兼容边权为负的情况
但是不能得到直径上具体有哪些点
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=5e5+5; //最大点数

int n; //点数

vector<pair<int,ll>> G[MAXN]; //邻接表

//deepest[i]:点i往下扎，最长路径是多少（可以不扎，必须初始化为0）
ll deepest[MAXN];
//longest[i]:只考虑子树i，过点i的最长路径是多少（直径可以是一个点，必须初始化为0）
ll longest[MAXN];

//直径长度
ll ans=0;

//树型dp求解直径长度
void dfs(int u,int f) {
    for(auto [v,w]:G[u]) {
        if(v!=f) {
            //先计算儿子的答案
            dfs(v,u);
            //先更新点u的longest数组
            //先前往下扎的最长是多少，接上当前儿子v往下扎，最长是多少
            longest[u]=max(longest[u],deepest[u]+w+deepest[v]);
            //更新全局最优长度
            ans=max(ans,longest[u]);
            //更新点u往下扎的最大长度
            deepest[u]=max(deepest[u],w+deepest[v]);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n-1;i++) {
        int u,v;cin>>u>>v;
        ll w;cin>>w;
        G[u].push_back({v,w});
        G[v].push_back({u,w});
    }

    //直接以1为根跑树型dp
    dfs(1,0);

    cout<<ans<<'\n';
    return 0;
}
