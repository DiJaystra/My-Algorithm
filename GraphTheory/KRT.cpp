#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=1e5+5; //最大点数
const int MAXM=3e5+5; //最大边数
const int LOG=20; //2^20 > MAXN*2

//点数，边数，查询数量
int n,m,q;

//边结构体
struct edge {
    int u,v;
    ll w;
};
//原图的边
edge E[MAXM];

//克鲁斯卡尔重构树，用邻接表法描述
//注意点的编号最多到达2*n-1
vector<int> tree[MAXN<<1];

//点权，用来代表边的权值
ll weight[MAXN<<1];

//点编号分配（记得从n+1开始分配新点）
int cntv=0;

//并查集
int parent[MAXN<<1];

//倍增表信息
int dep[MAXN<<1]; //深度
int jump[MAXN<<1][LOG]; //倍增祖先

//并查集查找根
int find(int x) {
    if(parent[x]==x) return x;
    return parent[x]=find(parent[x]);
}

//并查集加边
void merge(int x,int y,ll w) {
    x=find(x),y=find(y);
    if(x!=y) {
        //新点编号++
        cntv++;
        //新点连通两个连通块，作为根
        parent[x]=parent[y]=cntv;
        //点权拿来代表该边边权
        weight[cntv]=w;
        //在重构树上加边
        tree[cntv].push_back(x);
        tree[x].push_back(cntv);
        tree[cntv].push_back(y);
        tree[y].push_back(cntv);
    }
}

//克鲁斯卡尔重构树过程
void kruskal() {
    //并查集数组初始化
    for(int i=1;i<=2*n;i++) parent[i]=i;
    //边按照权值从小到大排序
    sort(E+1,E+m+1,[](const edge &x,const edge &y) {
        return x.w<y.w;
    });

    cntv=n; //点的编号从n+1开始分配

    //逐个考察边，如果能缩减连通分量数量，加边
    for(int i=1;i<=m;i++) {
        auto [u,v,w]=E[i];
        if(find(u)!=find(v)) {
            merge(u,v,w);
        }
    }
}

//dfs求深度信息和一级祖先
void dfs(int u,int f) {
    dep[u]=dep[f]+1;
    jump[u][0]=f;
    for(int v:tree[u]) {
        if(v!=f) {
            dfs(v,u);
        }
    }
}

//倍增求lca模板
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
    cin>>n>>m;
    for(int i=1;i<=m;i++) {
        int u,v;cin>>u>>v;
        ll w;cin>>w;
        E[i]={u,v,w};
    }

    //跑重构树过程
    kruskal();
    //图不一定连通，每棵树都跑一遍dfs
    for(int i=1;i<=cntv;i++) {
        //如果parent[i]==i，则该节点为某树根
        if(parent[i]==i) {
            dfs(i,0);
        }
    }
    //完善倍增表信息
    for(int j=1;j<LOG;j++) {
        for(int i=1;i<=cntv;i++) {
            jump[i][j]=jump[jump[i][j-1]][j-1];
        }
    }

    cin>>q;
    for(int i=1;i<=q;i++) {
        //查询s与t连通的最小瓶颈
        int s,t;cin>>s>>t;
        //如果不连通，输出impossible
        if(find(s)!=find(t)) {
            cout<<"impossible\n";
        }
        //连通，答案就是它们lca的权值
        else {
            int f=lca(s,t);
            cout<<weight[f]<<'\n';
        }
    }
    return 0;
}
