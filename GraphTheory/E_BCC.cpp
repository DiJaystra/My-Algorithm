#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=5e5+5; //最大点数
const int MAXM=2e6+5; //最大无向边数

int n,m; //点数，无向边数

//点的头边，边的下一条边，边的终点
int head[MAXN],nxt[MAXM*2],to[MAXM*2];
int cntg=1; //有向边编号从2开始分配

//节点的dfn编号，low值，以及E-BCC编号
int dfn[MAXN],low[MAXN],belong[MAXN];
int cntd=0; //dfn编号分配

int ebccSiz[MAXN]; //记录每一个E-BCC的大小
int ebccArr[MAXN]; //收集边双连通分量内的点的数组
//ebccl[i],ebccr[i]:E-BCC编号为i的点在ebccArr数组的分布范围
int ebccl[MAXN],ebccr[MAXN];
int idx=0; //当前收集到ebccArr的哪个索引
int ebccCnt=0; //E-BCC编号分配

int sta[MAXN]; //栈
int top=0; //栈顶

void addEdge(int u,int v) {
    nxt[++cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg;
}

//Tarjan算法求E-BCC
void tarjan(int u,int preEdge) {
    dfn[u]=low[u]=++cntd; //dfn序分配
    sta[++top]=u; //当前点入栈
    //遍历节点的所有出边
    for(int e=head[u];e!=0;e=nxt[e]) {
        //不能与来时的边是同一条无向边
        if(e==(preEdge^1)) continue;

        int v=to[e];
        //树边
        if(dfn[v]==0) {
            tarjan(v,e);
            low[u]=min(low[u],low[v]);
        }
        //回边
        else if(dfn[v]<dfn[u]) {
            low[u]=min(low[u],dfn[v]);
        }
    }
    //判断是否扎成口袋
    if(dfn[u]==low[u]) {
        ebccCnt++; //E-BCC编号+1
        ebccSiz[ebccCnt]=0; //准备计算该E-BCC大小
        ebccl[ebccCnt]=idx+1; //该E-BCC左区间
        int pop=-1;
        while(pop!=u) { //弹栈直至遇到u
            pop=sta[top--]; //弹栈
            belong[pop]=ebccCnt; //归属E-BCC
            ebccSiz[ebccCnt]++; //E-BCC大小+1
            ebccArr[++idx]=pop; //节点放入ebccArr数组
        }
        ebccr[ebccCnt]=idx; //该E-BCC右区间
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++) {
        int u,v;cin>>u>>v;
        addEdge(u,v);
        addEdge(v,u);
    }

    for(int i=1;i<=n;i++) {
        if(dfn[i]==0) tarjan(i,0);
    }

    cout<<ebccCnt<<'\n';
    for(int i=1;i<=ebccCnt;i++) {
        cout<<ebccSiz[i]<<' ';
        for(int j=ebccl[i];j<=ebccr[i];j++) {
            cout<<ebccArr[j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
