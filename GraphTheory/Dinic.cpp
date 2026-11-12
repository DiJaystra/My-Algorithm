/*
Dinic网络最大流模板
给定点数边数，源点汇点，以及网络图
求最大流
时间复杂度O(n*n*m)
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=205; //最大点数
const int MAXM=5005; //最大边数

//点数，边数
int n,m;
//源点编号，汇点编号
int s,t;

//链式前向星
int head[MAXN],nxt[MAXM<<1],to[MAXM<<1];
//边流量限制
ll limit[MAXM<<1];
//边从2开始编号，这样xor 1就是反向边
int cntg=1;

//每次从源点bfs的深度数组
int dep[MAXN];
//当前弧
int cur[MAXN];

//链式前向星加边
void addEdge(int u,int v,ll w) {
    nxt[++cntg]=head[u];
    to[cntg]=v;
    limit[cntg]=w;
    head[u]=cntg;
}

//bfs求当前残余网络的深度数组，并重置当前弧
void bfs() {
    for(int i=1;i<=n;i++) {
        dep[i]=n; //dep[i]=n表示不可达
        cur[i]=head[i]; //重置当前弧
    }

    //进行bfs
    queue<int> q;
    dep[s]=0;
    q.push(s);

    while(!q.empty()) {
        int u=q.front();q.pop();
        for(int e=head[u];e>0;e=nxt[e]) {
            int v=to[e];
            ll lim=limit[e];
            //当前的边有流量且未被访问过
            if(lim>0 && dep[v]==n) {
                dep[v]=dep[u]+1;
                q.push(v);
            }
        }
    }
}

//根据当前分层图，尽可能榨干边的流量
//参数：当前点，当前增广路的边权最小值
ll dinic(int u,ll rest) {
    //到达汇点，当前增广路全都榨rest
    if(u==t) return rest;

    //从当前点dfs下去，最多榨多少流量
    ll flow=0;
    //从当前弧出发
    //如果走完所有的边了，或者当前增广路剩余可用流量没了，退出循环
    for(int e=cur[u];e>0 && rest>0;e=nxt[e]) {
        cur[u]=e; //当前弧后移
        int v=to[e];
        ll lim=limit[e];
        //如果这条边是树边，且有流量
        if(dep[v]==dep[u]+1 && lim>0) {
            //往当前弧深了走，能榨多少流量
            ll receive=dinic(v,min(rest,lim));
            //流量增加
            flow+=receive;
            //剩余可用流量减少
            rest-=receive;
            //当前边的流量减少
            limit[e]-=receive;
            //反向边的流量增加
            limit[e^1]+=receive;
        }
    }

    return flow;
}

//Dinic算法整体调度
ll maxFlow() {
    //最大流答案初始化为0
    ll res=0;
    //bfs求深度数组并重置当前弧
    bfs();
    //汇点可达时，进入循环
    while(dep[t]!=n) {
        //根据当前分层图，尽可能榨干边的流量
        res+=dinic(s,LLONG_MAX);
        //重新求深度数组并重置当前弧
        bfs();
    }
    
    return res;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m>>s>>t;
    for(int i=1;i<=m;i++) {
        int u,v;cin>>u>>v;
        ll w;cin>>w;
        //正向边流量为w
        addEdge(u,v,w);
        //反向边流量为0
        addEdge(v,u,0);
    }

    //源点和汇点是同一个点时，流可无限大
    if(s==t) {
        cout<<"-1\n";
        return 0;
    }

    ll ans=maxFlow();
    cout<<ans<<'\n';
    return 0;
}
