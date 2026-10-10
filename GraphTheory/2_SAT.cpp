#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=1e6+5; //最大变量数

int n,m; //变量数，限制条数

vector<int> G[MAXN<<1]; //邻接表建图

//节点的dfn编号，low值，以及SCC编号
int dfn[MAXN<<1],low[MAXN<<1],belong[MAXN<<1];
int cntd=0; //dfn编号分配

int sccCnt=0; //SCC编号分配

int sta[MAXN<<1]; //栈
int top=0; //栈顶

bool ans[MAXN]; //解

//Tarjan算法
void tarjan(int u) {
    dfn[u]=low[u]=++cntd; //dfn序分配
    sta[++top]=u; //节点入栈
    for(int v:G[u]) {
        //树边
        if(dfn[v]==0) {
            tarjan(v);
            low[u]=min(low[u],low[v]);
        }
        else {
            //回边（指向当前Tarjan栈内节点的边）
            if(belong[v]==0) {
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
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=m;i++) {
        //x[u]为a 或 x[v]为b
        int u,a,v,b;cin>>u>>a>>v>>b;
        //先转换成表示变量
        if(a==0) u+=n;
        if(b==0) v+=n;

        //u的表示变量取反，指向v的表示变量
        if(a==0) G[u-n].push_back(v);
        else G[u+n].push_back(v);
        //v的表示变量取反，指向u的表示变量
        if(b==0) G[v-n].push_back(u);
        else G[v+n].push_back(u);
    }

    //图不一定全连通，每个点都考察是否来到
    //没来过就跑tarjan
    for(int u=1;u<=2*n;u++) {
        if(dfn[u]==0) tarjan(u);
    }

    for(int i=1;i<=n;i++) {
        //真变量和假变量在同一个SCC，无解
        if(belong[i]==belong[i+n]) {
            cout<<"IMPOSSIBLE\n";
            return 0;
        }
        else {
            //SCC编号从大到小是一个拓扑序
            //若真变量的SCC编号小，说明拓扑序靠后
            //此时取真变量成立，即该命题为真
            if(belong[i]<belong[i+n]) ans[i]=true;
            //反之取假变量成立，即该命题为假
            else ans[i]=false;
        }
    }

    //将解输出
    cout<<"POSSIBLE\n";
    for(int i=1;i<=n;i++) cout<<ans[i]<<' ';
    cout<<'\n';
    return 0;
}
