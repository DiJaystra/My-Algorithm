#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5;
int n; //节点数量

int parent[MAXN]; //并查集
int siz[MAXN]; //连通分量大小
int cnt=0; //连通分量数量
//查找节点的根
int find(int x) {
    if(parent[x]==x) return x;
    int root=find(parent[x]);
    return parent[x]=root;
}
//合并两节点的连通分量
void merge(int x,int y) {
    x=find(x),y=find(y);
    if(x!=y) {
        parent[x]=y;
        siz[y]+=siz[x];
        cnt--;
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    //连通分量初始化
    for(int i=1;i<=n;i++) {
        parent[i]=i;
        siz[i]=1;
    }
    cnt=n;

    int q;cin>>q;
    while(q--) {
        int op;cin>>op;
        if(op==1) { //合并
            int u,v;cin>>u>>v;
            merge(u,v);
        }
        else if(op==2) { //判断连通
            int u,v;cin>>u>>v;
            if(find(u)==find(v)) cout<<"YES\n";
            else cout<<"NO\n";
        }
    }
    return 0;
}