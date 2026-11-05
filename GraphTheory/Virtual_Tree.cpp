/*
二次排序求虚树模板
代码在每次查询中建立虚树并返回虚树的根
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=1e5+5; //原图最大点数
const int LOG=20; //2^LOG > MAXN

int n; //原图点数
int q; //查询数量
int m; //每次查询输入的关键点数量

//原图邻接表
vector<int> G[MAXN];
//虚树邻接表
vector<int> tree[MAXN];

//原图节点的深度数组、倍增数组
int dep[MAXN];
int jump[MAXN][LOG];

//原图节点的dfn序
int dfn[MAXN];
int cntd=0;

int arr[MAXN]; //关键点数组
int sorted[MAXN<<1]; //关键点添加lca，还未去重时，节点数量可能到达2*n

//dfs建立深度、倍增表、dfn信息
void dfs(int u,int f) {
    dep[u]=dep[f]+1;
    jump[u][0]=f;
    dfn[u]=++cntd;
    for(int v:G[u]) {
        if(v!=f) {
            dfs(v,u);
        }
    }
}

//将两节点带到同一深度
void toSame(int &x,int y) {
    int diff=dep[x]-dep[y];
    for(int i=LOG-1;i>=0;i--) {
        if((diff>>i)&1) {
            x=jump[x][i];
        }
    }
}

//寻找两节点的最近公共祖先
int lca(int x,int y) {
    if(dep[x]<dep[y]) swap(x,y);
    toSame(x,y);

    if(x==y) return x;

    for(int i=LOG-1;i>=0;i--) {
        if(jump[x][i]!=jump[y][i]) {
            x=jump[x][i];
            y=jump[y][i];
        }
    }

    return jump[x][0];
}

//构建虚树，并返回虚树根节点
//要求关键点数量>=1
int build() {
    //原始关键点，按照dfn序排序
    sort(arr+1,arr+m+1,[](const int &x,const int &y) {
        return dfn[x]<dfn[y];
    });

    //二次排序前，收集相邻关键点的lca
    int len=0; //sorted数组当前用到的下标
    for(int i=1;i<m;i++) {
        sorted[++len]=arr[i];
        sorted[++len]=lca(arr[i],arr[i+1]);
    }
    sorted[++len]=arr[m];
    //二次排序
    sort(sorted+1,sorted+len+1,[](const int &x,const int &y) {
        return dfn[x]<dfn[y];
    });

    //去重，得到虚树节点
    int unique=1;
    for(int i=2;i<=len;i++) {
        if(sorted[i]!=sorted[i-1]) {
            sorted[++unique]=sorted[i];
        }
    }

    //清空虚树节点的邻接表
    for(int i=1;i<=unique;i++) {
        tree[sorted[i]].clear();
    }
    //连边
    for(int i=1;i<unique;i++) {
        //只连 父->子 这个方向即可
        int f=lca(sorted[i],sorted[i+1]);
        tree[f].push_back(sorted[i+1]);
    }

    //返回虚树根节点
    return sorted[1];
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n-1;i++) {
        int u,v;cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    //dfs构建基本信息
    dfs(1,0);
    //倍增表初始化
    for(int j=1;j<LOG;j++) {
        for(int i=1;i<=n;i++) {
            jump[i][j]=jump[jump[i][j-1]][j-1];
        }
    }

    //处理查询
    cin>>q;
    for(int i=1;i<=q;i++) {
        cin>>m; //关键点数量
        for(int j=1;j<=m;j++) cin>>arr[j];
        int root=build(); //建虚树

        /*后续逻辑*/
    }
    return 0;
}