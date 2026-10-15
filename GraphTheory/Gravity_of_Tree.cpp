/*
树的重心有三种等价定义，这里按照第二种定义：
以某节点为根，该节点每棵子树的节点数不超过总节点数的一半
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=5e4+5; //最大点数

int n; //点数

vector<int> G[MAXN]; //邻接表

int siz[MAXN]; //子树大小

bool center[MAXN]; //点i是否为重心

//dfs求siz数组同时判断点u是否为重心
void dfs(int u,int f) {
    siz[u]=1;
    for(int v:G[u]) {
        if(v!=f) {
            dfs(v,u);
            siz[u]+=siz[v];
            //如果某棵子树v的大小超过总节点数一半
            if(siz[v]>n/2) center[u]=false;
        }
    }
    //u节点上方还有一棵“父子树”，大小也不能超过总节点数的一半
    if(n-siz[u]>n/2) center[u]=false;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n-1;i++) {
        int u,v;cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    //先认为所有节点都是重心，然后在dfs过程中剔除
    fill(center,center+MAXN,true);
    dfs(1,0);

    //编号从小到大输出重心节点编号（重心最多两个）
    for(int i=1;i<=n;i++) {
        if(center[i]) cout<<i<<' ';
    }
    cout<<'\n';
    return 0;
}
