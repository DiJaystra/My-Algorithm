#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//判断主串和模式串是否匹配
int KMP(string main,string pattern) {
    int n=main.size(),m=pattern.size();
    string merge=pattern+'#'+main;
    vector<int> pi(merge.size());
    for(int i=1;i<merge.size();i++) {
        int len=pi[i-1];
        while(len && merge[i]!=merge[len]) {
            len=pi[len-1];
        }
        if(merge[i]==merge[len]) {
            pi[i]=len+1;
            if(pi[i]==m) {
                return i-m*2; //匹配，返回模式串第一次匹配主串的主串匹配起点索引
            }
        }
    }
    return -1; //不匹配返回-1
}

//返回主串前缀和模式串后缀的最长匹配长度
int KMPfail(string main,string pattern) {
    int n=main.size(),m=pattern.size();
    string merge=pattern+'#'+main;
    vector<int> pi(merge.size());
    for(int i=1;i<merge.size();i++) {
        int len=pi[i-1];
        while(len && merge[i]!=merge[len]) {
            len=pi[len-1];
        }
        if(merge[i]==merge[len]) {
            pi[i]=len+1;
        }
    }
    return pi[merge.size()-1];
}