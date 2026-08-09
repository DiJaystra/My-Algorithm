#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=5e5+5; //原图最大点数
const int MAXM=1e6+5; //原图最大无向边数

int n,m; //原图点数、边数
int cntn; //方点编号分配

//原图
int head1[MAXN],nxt1[MAXM<<1],to1[MAXM<<1];
int cntg1=1; //有向边编号从2开始分配

//圆方树，注意点的数量可能翻倍
int head2[MAXN<<1],nxt2[MAXN<<2],to2[MAXN<<2];
int cntg2=1; //有向边编号从2开始分配

//节点的dfn编号，low值
int dfn[MAXN],low[MAXN];
int cntd=0; //dfn编号分配

int sta[MAXN]; //栈
int top=0; //栈顶

//原图加边
void addEdge1(int u,int v) {
    nxt1[++cntg1]=head1[u];
    to1[cntg1]=v;
    head1[u]=cntg1;
}
//圆方树加边
void addEdge2(int u,int v) {
    nxt2[++cntg2]=head2[u];
    to2[cntg2]=v;
    head2[u]=cntg2;
}

//Tarjan算法处理出圆方树
void tarjan(int u) {
    dfn[u]=low[u]=++cntd; //dfn序分配
    sta[++top]=u; //当前点入栈
    //遍历节点的所有出边
    for(int e=head1[u];e!=0;e=nxt1[e]) {
        int v=to1[e];
        if(dfn[v]==0) { //树边
            tarjan(v);
            low[u]=min(low[u],low[v]);
            //判断扎口袋
            if(low[v]>=dfn[u]) {
                cntn++;
                //u不能出栈，所以提前把它与V-BCC方点连接
                addEdge2(u,cntn);
                addEdge2(cntn,u);
                //开始弹栈
                int pop=-1;
                //到v停止，防止将u弹栈
                while(pop!=v) {
                    pop=sta[top--];
                    //方点与圆点连边
                    addEdge2(pop,cntn);
                    addEdge2(cntn,pop);
                }
            }
        }
        else if(dfn[v]<dfn[u]) { //回边
            low[u]=min(low[u],dfn[v]);
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    cntn=n;
    for(int i=1;i<=m;i++) {
        int u,v;cin>>u>>v;
        addEdge1(u,v);
        addEdge1(v,u);
    }
    for(int i=1;i<=n;i++) {
        if(dfn[i]==0) tarjan(i);
    }
    return 0;
}
