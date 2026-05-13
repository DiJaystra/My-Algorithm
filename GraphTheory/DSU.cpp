#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int MAXN=2e5+5;
int n; //节点数量

vector<int> parent(MAXN,1); //并查集
vector<int> siz(MAXN); //连通分量大小
int cnt=0; //连通分量数量
//查找节点的根
int Find(int x) {
    if(parent[x]==x) return x;
    int root=Find(parent[x]);
    return parent[x]=root;
}
//合并两节点的连通分量
void Union(int x,int y) {
    int rx=Find(x),ry=Find(y);
    if(rx!=ry) {
        parent[rx]=ry;
        siz[ry]+=siz[rx];
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
            Union(u,v);
        }
        else if(op==2) { //判断连通
            int u,v;cin>>u>>v;
            if(Find(u)==Find(v)) cout<<"YES\n";
            else cout<<"NO\n";
        }
    }
    return 0;
}