#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=2e5+5; //字典树最大总节点数,设为字符串最大总长度
int trie[MAXN][26]; //只考虑小写字母
int pass[MAXN]; //节点前缀统计
int all[MAXN]; //命名为end含义冲突
int cnt=1; //节点编号分配，1为根，0为空结点

//插入单词
void insert(string word) {
    int cur=1;
    pass[cur]++;
    for(char ch:word) {
        int path=ch-'a';
        if(trie[cur][path]==0) {
            trie[cur][path]=++cnt;
        }
        cur=trie[cur][path];
        pass[cur]++;
    }
    all[cur]++;
}
//查找单词个数
int search(string word) {
    int cur=1;
    for(char ch:word) {
        int path=ch-'a';
        if(trie[cur][path]==0) return 0;
        cur=trie[cur][path];
    }
    return all[cur];
}
//查找前缀单词个数
int prefix(string word) {
    int cur=1;
    for(char ch:word) {
        int path=ch-'a';
        if(trie[cur][path]==0) return 0;
        cur=trie[cur][path];
    }
    return pass[cur];
}
//删除单词
void erase(string word) {
    if(search(word)==0) return;
    int cur=1;
    for(char ch:word) {
        int path=ch-'a';
        if(--pass[trie[cur][path]]==0) {
            trie[cur][path]=0;
            return;
        }
        cur=trie[cur][path];
    }
    all[cur]--;
}
//清空所有字符串
void clear() {
    for(int i=1;i<=cnt;i++) {
        for(int j=0;j<26;j++) {
            trie[i][j]=0;
        }
        all[i]=0;
        pass[i]=0;
    }
    cnt=1;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    int q;cin>>q;
    while(q--) {
        int op;cin>>op;
        string word;cin>>word;
        if(op==1) { //插入单词
            insert(word);
        }
        else if(op==2) { //删除单词
            erase(word);
        }
        else if(op==3) { //查找单词个数
            cout<<search(word)<<'\n';
        }
        else { //查找前缀单词个数
            cout<<prefix(word)<<'\n';
        }
    }
    return 0;
}