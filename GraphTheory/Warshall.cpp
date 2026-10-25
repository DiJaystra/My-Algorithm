/*
传递闭包：若a->b成立，b->c成立，一定有a->c成立
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=105; //最大点数

int n; //点数

//dp[i][j]:i->j是否成立
bitset<MAXN> dp[MAXN];

//warshall算法求传递闭包
void warshall() {
    //枚举中转点
    for(int k=1;k<=n;k++) {
        //枚举起点
        for(int i=1;i<=n;i++) {
            //如果有关系i->k
            if(dp[i][k]) {
                dp[i]|=dp[k];
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    //输入关系矩阵
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            int x;cin>>x;
            dp[i][j]=x;
        }
    }

    warshall();

    //输出关系矩阵的传递闭包
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=n;j++) {
            cout<<dp[i][j]<<' ';
        }
        cout<<'\n';
    }
    return 0;
}
