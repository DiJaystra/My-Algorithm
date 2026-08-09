//点双连通分量模板
//这里定义V-BCC为不含割点的子图
//特别地，代码认为孤立点是单独的一个V-BCC
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=5e5+5; //最大点数
const int MAXM=2e6+5; //最大无向边数

int n,m; //点数，无向边数

//点的头边，边的下一条边，边的终点
int head[MAXN],nxt[MAXM<<1],to[MAXM<<1];
int cntg=1; //有向边编号从2开始分配

//节点的dfn编号，low值
int dfn[MAXN],low[MAXN];
int cntd=0; //dfn编号分配

int vbccSiz[MAXN]; //记录每一个V-BCC的大小
int vbccArr[MAXN<<1]; //收集点双连通分量内的点的数组
//vbccl[i],vbccr[i]:V-BCC编号为i的点在vbccArr数组的分布范围
int vbccl[MAXN],vbccr[MAXN];
int idx=0; //当前收集到vbccArr的哪个索引
int vbccCnt=0; //V-BCC编号分配

int sta[MAXN]; //栈
int top=0; //栈顶

void addEdge(int u,int v) {
    nxt[++cntg]=head[u];
    to[cntg]=v;
    head[u]=cntg;
}

void tarjan(int u) {
    dfn[u]=low[u]=++cntd; //dfn序分配
    sta[++top]=u; //当前点入栈
    //遍历节点的所有出边
    for(int e=head[u];e!=0;e=nxt[e]) {
        int v=to[e];
        if(dfn[v]==0) { //树边
            tarjan(v);
            low[u]=min(low[u],low[v]);
            //判断扎口袋
            if(low[v]>=dfn[u]) {
                vbccCnt++; //V-BCC编号+1
                //u不能出栈，所以提前把它归属到V-BCC
                vbccSiz[vbccCnt]=1;
                vbccArr[++idx]=u;
                vbccl[vbccCnt]=idx; //该V-BCC左区间
                //开始弹栈
                int pop=-1;
                //到v停止，防止将u弹栈
                while(pop!=v) {
                    pop=sta[top--];
                    vbccSiz[vbccCnt]++;
                    vbccArr[++idx]=pop;
                }
                vbccr[vbccCnt]=idx; //该V-BCC右区间
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
    for(int i=1;i<=m;i++) {
        int u,v;cin>>u>>v;
        if(u!=v) { //忽略自环
            addEdge(u,v);
            addEdge(v,u);
        }
    }

    for(int u=1;u<=n;u++) {
        if(dfn[u]==0) {
            //孤立点需要特判，自己归属一个V-BCC
            if(head[u]==0) {
                vbccCnt++;
                vbccSiz[vbccCnt]=1;
                vbccArr[++idx]=u;
                vbccl[vbccCnt]=vbccr[vbccCnt]=idx;
            }
            else {
                tarjan(u);
            }
        }
    }

    //输出各V-BCC信息
    cout<<vbccCnt<<'\n';
    for(int i=1;i<=vbccCnt;i++) {
        cout<<vbccSiz[i]<<' ';
        for(int j=vbccl[i];j<=vbccr[i];j++) {
            cout<<vbccArr[j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
