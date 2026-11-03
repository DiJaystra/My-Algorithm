/*
无向图求字典序最小的欧拉路
如果不需要字典序最小，去除排序过程
如果是欧拉图，得到欧拉回路
如果是半欧拉图，得到欧拉路径
如果不存在欧拉路，输出No
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //最大点数
const int MAXM=2e5+5; //最大边数

int n,m; //点数，边数

//{出边终点，出边对应无向边编号}
struct to {
    int v,id;
};
vector<to> G[MAXN]; //邻接表
//cur[u]:邻接表G[u]当前用到下标为cur[u]的出边
int cur[MAXN];

//节点的度（无向图不区分出入度）
int deg[MAXN];

//vis[i]:无向边i是否被走过
bool vis[MAXM];

//欧拉路数组
vector<int> path;

//找到可能的起点
int findStart() {
    //起点和终点，初始时-1，表示没有定
    int s=-1,t=-1;
    for(int i=1;i<=n;i++) {
        //是奇点，且起点终点已定，说明有>2个奇点，无欧拉路
        if((deg[i]&1) && s!=-1 && t!=-1) return -1;
        //是奇点
        if(deg[i]&1) {
            //起点定了那就定终点，否则定起点
            if(s!=-1) t=i;
            else s=i;
        }
    }
    //如果有起点没终点或者无起点有终点（这种情况实际不存在）
    if((s==-1)^(t==-1)) return -1;

    //如果定了起点
    if(s!=-1) return s;

    //都是偶点，找第一个非孤立点
    for(int i=1;i<=n;i++) {
        if(deg[i]>0) return i;
    }

    //都是孤立点，已在main中特判
    return -1;
}

//Hierholzer算法找欧拉路
void euler(int u) {
    //当前出边还没用完
    while(cur[u]<(int)G[u].size()) {
        auto [v,id]=G[u][cur[u]]; //当前出边终点和对应无向边编号
        cur[u]++; //出边后移
        if(vis[id]) continue; //若该无向边已被访问
        vis[id]=true; //标记无向边已访问
        euler(v);
    }
    //出边用完了，收集进欧拉路数组
    path.push_back(u);
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++) {
        int u,v;cin>>u>>v;
        G[u].push_back({v,i});
        G[v].push_back({u,i});
        deg[u]++,deg[v]++;
    }

    //没有边，欧拉路直接是一个点
    if(m==0) {
        cout<<"1\n";
        return 0;
    }

    //为了字典序最小，按照出边终点排序
    for(int i=1;i<=n;i++) {
        sort(G[i].begin(),G[i].end(),[](const to &x,const to &y) {
            return x.v<y.v;
        });
    }

    //可能的起点
    int s=findStart();

    //不存在可能的起点
    if(s==-1) {
        cout<<"No\n";
        return 0;
    }

    //从可能的起点开始找欧拉路
    euler(s);

    //如果不是欧拉路（剩余图不是连通的）
    if((int)path.size()<m+1) {
        cout<<"No\n";
        return 0;
    }

    //欧拉路数组倒着看才是真正的欧拉路
    reverse(path.begin(),path.end());
    for(int x:path) cout<<x<<' ';
    cout<<'\n';
    return 0;
}
