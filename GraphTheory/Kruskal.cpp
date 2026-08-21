#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //最大顶点数
const int MAXM=2e5+5; //最大边数

int n,m; //顶点数，边数

int parent[MAXN]; //并查集
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
    }
}

//边结构体
struct edge {
    int u,v;
    ll w;
};

edge E[MAXM]; //存储边
edge selected[MAXM]; //最小生成树所选边

void kruskal() {
    //连通分量初始化
    for(int i=1;i<=n;i++) {
        parent[i]=i;
    }
    //边按权值升序排序
    sort(E+1,E+m+1,[](edge x,edge y){
        return x.w<y.w;
    });
    int cnt=0; //已选边数
    for(int i=1;i<=m;i++) {
        if(cnt>=n-1) break;
        auto [u,v,w]=E[i];
        if(find(u)!=find(v)) {
            selected[++cnt]=E[i];
            merge(u,v);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++) {
        int u,v;cin>>u>>v;
        ll w;cin>>w;
        E[i]={u,v,w};
    }
    kruskal();
    return 0;
}