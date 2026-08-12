#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=105; //未知数、方程 的最大数量

int n,m;  //n个方程，m个未知数
bitset<MAXN> mat[MAXN]; //增广矩阵

//高斯消元
void gauss() {
    int all=max(n,m);
    //遍历每个未知数，处理第i列
    for(int i=1;i<=all;i++) {
        //找哪一行在当前列是1
        int best=i;
        for(int j=1;j<=all;j++) {
            //跳过主元行
            if(j<i && mat[j][j]) continue;
            //在非主元行中找该列是1的
            if(mat[j][i]) {
                best=j;
                break;
            }
        }
        //将best行挪到第i行
        swap(mat[i],mat[best]);
        //如果这一列真的有1
        if(mat[i][i]) {
            //给其它行中，该列是1的进行消元操作
            for(int j=1;j<=all;j++) {
                if(j!=i && mat[j][i]) {
                    mat[j]^=mat[i];
                }
            }
        }
    }
}
/*
消元完成后，x_i如果是主元，则第i列只有第i行为1，其余为0
对于每一行，如果主元位置为0，则该行全部系数列为0
反之主元位置右侧自由元处的系数可能不为0，其余为0

若要判断解的情况，先判断无解，再判断多解
检查前n行，如果出现矛盾方程（主元位置为0，增广列非0），则无解
若有解，检查前m列，如果主元位置为0，则多解
反之有唯一解，增广列即为解
*/

//打印增广矩阵
void show() {
    int all=max(n,m);
    for(int i=1;i<=all;i++) {
        for(int j=1;j<=all+1;j++) {
            cout<<mat[i][j]<<' ';
        }
        cout<<'\n';
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    int all=max(n,m);
    //第i个方程
    for(int i=1;i<=n;i++) {
        //有num个未知数数参与异或运算
        int num;cin>>num;
        for(int j=1;j<=num;j++) {
            int pos;cin>>pos;
            //第pos个未知数的系数设为1
            mat[i].set(pos);
        }
        //这个方程的异或结果
        int res;cin>>res;
        mat[i][all+1]=res;
    }
    gauss();
    show();
    return 0;
}