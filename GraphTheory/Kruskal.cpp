#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int MAXN=2e5+5; //最大顶点数、边数
int n,m; //顶点数，边数

vector<int> parent(MAXN); //并查集
//查找节点的根
int Find(int x) {
    return parent[x]==x ? x : parent[x]=Find(parent[x]);
}
//合并两节点的连通分量
void Union(int x,int y) {
    int rootx=Find(x),rooty=Find(y);
    if(rootx!=rooty) {
        parent[rootx]=rooty;
    }
}

//边结构体
struct E {
    int u,v;
    ll w;
};

vector<E> edges(MAXN); //存储边
vector<E> selected(MAXN); //最小生成树所选边

void kruskal() {
    //连通分量初始化
    for(int i=1;i<=n;i++) {
        parent[i]=i;
    }
    //边按权值升序排序
    sort(edges.begin()+1,edges.begin()+m+1,
    [](E x,E y){
        return x.w<y.w;
    });
    int cnt=0; //已选边数
    for(int i=1;i<=m;i++) {
        if(cnt>=n-1) break;
        auto [u,v,w]=edges[i];
        if(Find(u)!=Find(v)) {
            selected[++cnt]=edges[i];
            Union(u,v);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++) {
        int u,v;cin>>u>>v;
        ll w;cin>>w;
        edges[i]={u,v,w};
    }
    kruskal();
    return 0;
}