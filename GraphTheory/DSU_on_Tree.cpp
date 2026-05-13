#include<bits/stdc++.h>
using namespace std;
using ll=long long;

//例题：以1为根节点，求所有子树的不同颜色种类数（每个节点都有一个颜色）

int n; //节点个数
vector<int> color; //每个节点的颜色
vector<vector<int>> G; //邻接表
vector<int> ans; //预处理的答案
vector<int> fa,siz,son; //树链剖分参数
vector<int> cntColor; //记录每种颜色出现次数
int diff=0; //当前不同颜色的种类数

//设置father,size,heavy_son
void dfs1(int u,int f) { //当前节点，当前节点的父亲节点
    fa[u]=f;
    siz[u]=1; //子树大小初始化为自己一个，等会加上儿子的子树大小
    for(int v : G[u]) {
        if(v!=f) dfs1(v,u);
    }
    for(int v : G[u]) {
        if(v!=f) {
            siz[u]+=siz[v];
            if(son[u]==-1 || siz[son[u]] < siz[v]) son[u]=v; //更新重儿子
        }
    }
}
//生效函数：u子树所有节点的颜色重新贡献
void effect(int u) {
    if(++cntColor[color[u]]==1) diff++;
    for(int v:G[u]) {
        if(v!=fa[u]) effect(v);
    }
}
//取消函数：取消子树u对答案的贡献
void cancel(int u) {
    if(--cntColor[color[u]]==0) diff--;
    for(int v:G[u]) {
        if(v!=fa[u]) cancel(v);
    }
}
//统计每个子树的答案
void dfs2(int u,int keep) { //u当前节点，keep当前节点的答案贡献是否保留
    //计算轻儿子的答案
    for(int v:G[u]) {
        if(v!=fa[u] && v!=son[u]) dfs2(v,0);
    }
    if(son[u]!=-1) dfs2(son[u],1); //计算重儿子的答案
    if(++cntColor[color[u]]==1) diff++; //节点u自己贡献答案
    //所有轻儿子的答案重新贡献
    for(int v:G[u]) {
        if(v!=fa[u] && v!=son[u]) effect(v);
    }
    ans[u]=diff; //得到子树u的答案
    if(keep==0) cancel(u); //不保留则取消u节点对答案的贡献
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    G.resize(n+1);
    color.resize(n+1);
    ans.resize(n+1);
    for(int i=0;i<n-1;i++) {
        int u,v;cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i=1;i<=n;i++) cin>>color[i];

    fa.assign(n+1,-1);
    siz.assign(n+1,-1);
    son.assign(n+1,-1);
    cntColor.resize(n+1);
    dfs1(1,0);
    dfs2(1,0);

    int m;cin>>m;
    while(m--) {
        int u;cin>>u;
        cout<<ans[u]<<'\n';
    }
    return 0;
}