//AC自动机模板
//快速计算n个模式串匹配文章的次数
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //目标串最大数量
const int MAXS=2e5+5; //目标串总长度最大值

int n; //目标串的个数

string passage; //文章字符串

//AC自动机的直通表，忽略fail指针则为字典树
int trie[MAXS][26];
//每个节点的失配指针
int fail[MAXS];
//节点编号分配
int cnt=0;

//ending[i]:目标串i的结尾节点编号
int ending[MAXN];
//times[i]:字典树节点i在文章中的出现次数
int times[MAXS];

//链式前向星建fail指针反图，实际上是一棵树
int head[MAXS],nxt[MAXS],to[MAXS];
void addEdge(int id,int u,int v) {
    nxt[id]=head[u];
    to[id]=v;
    head[u]=id;
}

//插入第id个目标串
void insert(int id,string &word) {
    int cur=0;
    for(char ch:word) {
        int path=ch-'a';
        if(trie[cur][path]==0) {
            trie[cur][path]=++cnt;
        }
        cur=trie[cur][path];
    }
    ending[id]=cur;
}

//设置好fail指针，同时设置直通表
void setFail() {
    //BFS初始化AC自动机
    queue<int> q; //队列存的是节点编号

    //将第一层节点放入队列当中
    for(int i=0;i<26;i++) {
        if(trie[0][i]>0) {
            q.push(trie[0][i]);
        }
    }

    //设置fail指针，同时设置直通表trie
    while(!q.empty()) {
        int u=q.front();q.pop();
        for(int i=0;i<26;i++) {
            //如果当前路径的儿子不存在，那就更新直通表
            if(trie[u][i]==0) {
                trie[u][i]=trie[fail[u]][i];
            }
            //反之更新儿子的fail指针
            else {
                fail[trie[u][i]]=trie[fail[u]][i];
                q.push(trie[u][i]);
            }
        }
    }
}

//汇总节点编号u的词频
void gather(int u) {
    for(int ei=head[u];ei!=0;ei=nxt[ei]) {
        int v=to[ei];
        gather(v);
        times[u]+=times[v];
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    //读入目标串
    for(int i=1;i<=n;i++) {
        string s;cin>>s;
        insert(i,s);
    }
    //设置好fail指针，以及直通表
    setFail();

    //读入文章
    cin>>passage;
    //统计单点词频出现次数
    for(int u=0,i=0;i<passage.size();i++) {
        u=trie[u][passage[i]-'a']; //根据直通表，找到下一个节点
        times[u]++; //增加单点匹配次数
    }

    //基于fail指针建反图
    for(int i=1;i<=cnt;i++) {
        addEdge(i,fail[i],i);
    }
    //汇总答案
    gather(0);

    //输出答案
    for(int i=1;i<=n;i++) {
        cout<<times[ending[i]]<<'\n';
    }
    return 0;
}
