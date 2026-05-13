#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;

//例题：二维网格，给定起点终点，求最短距离
//有些格子上有障碍，而且每次只能上下左右走
//这题一眼bfs，当然也能dijkstra，虽然耗时
//而A*算法结合了这俩，dijkstra是它的特例，且代码近似dijkstra
//A*会估计当前点到终点的距离，从而实现“吸引”到终点的趋势
//而估计到终点的距离需要一个启发函数(常用的是下面那三个f函数)
//估计函数的选择是不能乱选的，其估计数值应<=当前点到终点的真实最短距离，否则引力过强
//对比dijkstra，其不估计当前点到终点距离，可认为估计了0，无引力

int n,m;
int startx,starty,targetx,targety;
vector<string> G;

pair<int,int> dxy[4]={{1,0},{-1,0},{0,1},{0,-1}};

//曼哈顿距离
int f1(int x,int y) {
    return abs(targetx-x)+abs(targety-y);
}
//对角线距离（切比雪夫距离）
int f2(int x,int y) {
    return max(abs(targetx-x),abs(targety-y));
}
//几何距离（欧拉距离）
ld f3(int x,int y) {
    return sqrt(pow(targetx-x,2)+pow(targety-y,2));
}

int Astar() {
    if(G[startx][starty]=='#' || G[targetx][targety]=='#') {
        return -1;
    }

    vector<vector<int>> dist(n,vector<int>(m,INT_MAX));
    dist[startx][starty]=0;
    
    using tp=tuple<int,int,int>; //A星距离(起点到当前点距离+预估距离)，点坐标
    priority_queue<tp,vector<tp>,greater<>> pq;
    //这里使用曼哈顿距离来估计
    pq.push({f1(startx,starty),startx,starty});
    while(!pq.empty()) {
        auto [now,ux,uy]=pq.top();pq.pop(); //注意这里now是用不上的，仅用于堆比较
        if(dist[ux][uy]==INT_MAX) {
            continue;
        }
        if(ux==targetx && uy==targety) {
            return dist[ux][uy];
        }
        for(auto [dx,dy]:dxy) {
            int vx=ux+dx;
            int vy=uy+dy;
            if(vx<0 || vx>=n || vy<0 || vy>=m) continue;
            if(G[vx][vy]=='.' && dist[ux][uy]+1 < dist[vx][vy]) {
                dist[vx][vy]=dist[ux][uy]+1;
                pq.push({dist[vx][vy]+f1(vx,vy),vx,vy});
            }
        }
    }

    return -1;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);

    cin>>n>>m;
    cin>>startx>>starty>>targetx>>targety;
    startx--,starty--,targetx--,targety--;
    G.resize(n);
    for(int i=0;i<n;i++) {
        cin>>G[i];
    }

    cout<<Astar()<<'\n';

    return 0;
}