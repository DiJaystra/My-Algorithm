#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=1e5+5;
int n,m; //节点数，边数
vector<vector<int>> G(MAXN); //邻接表

//节点的dfn编号，low值，以及SCC编号
vector<int> dfn(MAXN),low(MAXN),belong(MAXN);
int cntd=0; //dfn编号分配

vector<int> sccSiz(MAXN); //记录每一个SCC的大小
int sccCnt=0; //SCC编号分配

vector<int> sta(MAXN); //栈
int top=0; //栈顶

//Tarjan算法
void tarjan(int u) {
    dfn[u]=low[u]=++cntd; //dfn序分配
    sta[++top]=u; //节点入栈
    for(int v:G[u]) {
        if(dfn[v]==0) { //树边
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else {
            if(belong[v]==0) { //回边
                low[u]=min(low[u],dfn[v]);
            }
        }
    }
    if(dfn[u]==low[u]) { //扎成口袋，开始结算SCC
        sccCnt++;
        int pop=-1;
        while(pop!=u) {
            pop=sta[top--]; //弹栈
            belong[pop]=sccCnt; //归属SCC
            sccSiz[sccCnt]++;
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    for(int i=0;i<m;i++) {
        int u,v;cin>>u>>v;
        G[u].push_back(v);
    }
    for(int i=1;i<=n;i++) if(dfn[i]==0) tarjan(i);
    return 0;
}