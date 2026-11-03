/*
有向图求字典序最小的欧拉路
如果不需要字典序最小，去除排序过程
如果是欧拉图，得到欧拉回路
如果是半欧拉图，得到欧拉路径
如果不存在欧拉路，输出No
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //最大点数

int n,m; //点数，边数

vector<int> G[MAXN]; //邻接表

//节点的出度、入度
int outdeg[MAXN],indeg[MAXN];

//cur[u]:邻接表G[u]当前用到下标为cur[u]的出边
int cur[MAXN];

//欧拉路数组
vector<int> path;

//找到欧拉路可能的起点
int findStart() {
    //起点和终点，初始时-1，表示没有定
    int s=-1,t=-1;
    for(int i=1;i<=n;i++) {
        int v=outdeg[i]-indeg[i];
        //出入度差距超过1，或者想作为起点但已经有起点，想作为终点但已经有终点
        if(v<-1 || v>1 || (v==1 && s!=-1) || (v==-1 && t!=-1)) return -1;
        //出度比入度多1，作为起点
        if(v==1) s=i;
        //入度比出度多1，作为终点
        else if(v==-1) t=i;
    }
    //如果有起点没终点或者无起点有终点
    if((s==-1)^(t==-1)) return -1;

    //如果定了起点，直接返回
    if(s!=-1) return s;

    //此时每个点出度都等于入度
    //找到非孤立点，作为起点即可
    //这里找最小的非孤立点作为起点，满足字典序最小的条件
    for(int i=1;i<=n;i++) {
        if(outdeg[i]>0) {
            return i;
        }
    }

    //全是孤立点，返回-1（此特殊情况已在main特判）
    return -1;
}

//Hierholzer算法找欧拉路
void euler(int u) {
    //当前出边还没用完
    while(cur[u]<(int)G[u].size()) {
        int v=G[u][cur[u]]; //当前出边终点
        cur[u]++; //出边后移
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
        G[u].push_back(v);
        outdeg[u]++,indeg[v]++;
    }

    //没有边，欧拉路直接是一个点
    if(m==0) {
        cout<<"1\n";
        return 0;
    }

    //为了字典序最小，排序
    for(int i=1;i<=n;i++) {
        sort(G[i].begin(),G[i].end());
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

    //如果不是欧拉路（还有边没走到）
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
