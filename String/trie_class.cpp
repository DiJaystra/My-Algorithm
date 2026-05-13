#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//字典树节点结构体
struct TrieNode {
    TrieNode* next[26]; //只包含小写字母（有其它字符则可以考虑用map<int,TrieNode*>）
    int end; //完整字符串计数
    int pass; //前缀计数

    //创建节点
    TrieNode() {
        for(int i=0;i<26;i++) {
            next[i]=nullptr;
        }
        end=0;
        pass=0;
    }
};

class Trie {
private:
    TrieNode* root; //根节点

public:
    //构造函数初始化根节点
    Trie() {
        root=new TrieNode();
    }

    //插入单词到字典树中
    void insert(const string &word) {
        TrieNode* node=root;
        node->pass++;
        for(char ch:word) {
            int idx=ch-'a';
            if(!node->next[idx]) node->next[idx]=new TrieNode();
            node=node->next[idx];
            node->pass++;
        }
        node->end++;
    }

    //查询单词出现了几次
    int search(const string &word) {
        TrieNode* node=root;
        for(char ch:word) {
            int idx=ch-'a';
            if(!node->next[idx]) return 0;
            node=node->next[idx];
        }
        return node->end;
    }

    //查询以prefix为前缀的单词数量
    int prefixCount(const string &prefix) {
        TrieNode* node=root;
        for(char ch:prefix) {
            int idx=ch-'a';
            if(!node->next[idx]) return 0;
            node=node->next[idx];
        }
        return node->pass;
    }

    //如果存在单词word，删除该词频一次；若不存在则什么也不做
    void erase(const string &word) {
        if(search(word)==0) return;
        TrieNode* node=root;
        node->pass--;
        for(char ch:word) {
            int idx=ch-'a';
            if(--node->next[idx]->pass==0) {
                node->next[idx]=nullptr;
                return;
            }
            node=node->next[idx];
        }
        node->end--;
    }
};

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    int n;cin>>n;
    Trie trie;
    while(n--) {
        int op;cin>>op;
        if(op==1) { //插入一个字符串s
            string s;cin>>s;
            trie.insert(s);
        }
        else if(op==2) { //查询是否含有字符串s
            string s;cin>>s;
            if(trie.search(s)) {
                cout<<"YES\n";
            }
            else {
                cout<<"NO\n";
            }
        }
        else if(op==3) { //查询以prefix为前缀的单词数量
            string prefix;cin>>prefix;
            cout<<trie.prefixCount(prefix)<<'\n';
        }
        else { //删除字符串s（如果出现过）
            string s;cin>>s;
            trie.erase(s);
        }
    }
    return 0;
}