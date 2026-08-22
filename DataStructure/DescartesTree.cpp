//这里以小根堆的笛卡尔树为例
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=1e7+5; //最大数组长度

int n; //数组长度
int a[MAXN]; //原数组

//笛卡尔树，每个节点的左儿子和右儿子
int lc[MAXN],rc[MAXN];
int root=0; //笛卡尔树根节点

//建树辅助栈
int sta[MAXN];
int top=0; //栈顶

//多例子清空
void prepare() {
    for(int i=1;i<=n;i++) {
        lc[i]=rc[i]=0;
    }
    top=0;
}

//基于栈的O(n)建树
void build() {
    for(int i=1;i<=n;i++) {
        int pos=top; //记录弹出后的栈顶位置
        //小根堆，栈递增（不严格）
        while(pos > 0 && a[sta[pos]] > a[i]) pos--;
        //如果栈中还有元素，栈顶右儿子指向i
        if(pos>0) rc[sta[pos]]=i;
        //如果真的有弹出，i的左儿子指向最近一次弹出节点
        if(pos<top) lc[i]=sta[pos+1];
        //如果栈空，说明这是前缀严格最小值，作为新根
        if(pos==0) root=i;
        //当前节点入栈
        sta[++pos]=i;
        //更新栈顶位置
        top=pos;
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    prepare();
    for(int i=1;i<=n;i++) cin>>a[i];
    build();

    ll ans1=0,ans2=0;
    for(int i=1;i<=n;i++) {
        ans1^=1LL*i*(lc[i]+1);
        ans2^=1LL*i*(rc[i]+1);
    }
    cout<<ans1<<' '<<ans2<<'\n';
    return 0;
}