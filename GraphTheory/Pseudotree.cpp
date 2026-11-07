/*
基环树模板
找出一个图中所有连通块的唯一环
图保证所有连通块一定都是基环树
模板支持基环为自环（一元环）或重边（二元环）的情况
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //最大点数

int n; //点数

vector<int> G[MAXN]; //原图邻接表

int dfn[MAXN]; //节点dfn序
int cntd=0; //dfn序分配

int from[MAXN]; //节点的前驱，用于还原环

//circle[i]:连通块i的基环
vector<int> circle[MAXN];
//连通分量编号
int block=0;

//dfs找基环
void dfs(int u) {
    dfn[u]=++cntd; //节点分配dfn
    for(int v:G[u]) {
        //是树边
        if(dfn[v]==0) {
            //前驱记录
            from[v]=u;
            //深入递归
            dfs(v);
        }
        //找到环了（等号出现在自环的情形）
        else if(dfn[u]<=dfn[v]) {
            //把环按顺序还原出来
            for(int cur=v;cur!=u;cur=from[cur]) {
                circle[block].push_back(cur);
            }
            circle[block].push_back(u);
            //找到环之后不急着退出，先给连通块每个点都分配完dfn
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) {
        int u,v;cin>>u>>v;
        //如果是自环，只加入一次
        if(u==v) G[u].push_back(v);
        else {
            G[u].push_back(v);
            G[v].push_back(u);
        }
    }

    for(int i=1;i<=n;i++) {
        //找到新的连通块，就dfs遍历找基环
        if(dfn[i]==0) {
            block++;
            dfs(i);
        }
    }
    return 0;
}
