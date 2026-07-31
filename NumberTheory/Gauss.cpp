#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;

const int MAXN=105; //未知数、方程 的最大数量
//若数字绝对值小于ESP，认为是0，反之认为不是0
const double EPS=1e-7;

int n,m; //n个方程，m个未知数
double mat[MAXN][MAXN]; //增广矩阵

//输出增广矩阵
void show() {
    int all=max(n,m);
    for(int i=1;i<=all;i++) {
        for(int j=1;j<=all+1;j++) {
            cout<<mat[i][j]<<' ';
        }
        cout<<'\n';
    }
}

//高斯消元法标准过程（行简化的非严格阶梯型）
//是区分唯一解、无解、多解的写法
void gauss() {
    int all=max(n,m);
    //处理第i个列
    for(int i=1;i<=all;i++) {
        int best=i; //找第i列中，主元最大的行
        for(int j=1;j<=all;j++) {
            //从第一行开始遍历，当前非主元行和大于等于i行的参与PK
            if(j<i && abs(mat[j][j])>=EPS) {
                continue;
            }
            if(abs(mat[j][i])>abs(mat[best][i])) {
                best=j;
            }
        }
        //把主元最大的行提到第i行
        swap(mat[i],mat[best]);
        //如果该列确实有非零系数，消其它列
        if(abs(mat[i][i])>=EPS) {
            double tmp=mat[i][i];
            //先把本行主元设成1
            for(int j=i;j<=all+1;j++) {
                mat[i][j]/=tmp;
            }
            //把其他行在该列的值消成0
            for(int j=1;j<=all;j++) {
                if(i!=j) {
                    double rate=mat[j][i]/mat[i][i];
                    for(int k=i;k<=all+1;k++) {
                        mat[j][k]-=mat[i][k]*rate;
                    }
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

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    int all=max(n,m);
    for(int i=1;i<=n;i++) {
        for(int j=1;j<=m+1;j++) {
            if(j==m+1) {
                cin>>mat[i][all+1];
            }
            else cin>>mat[i][j];
        }
    }
    gauss();
    show();
    return 0;
}