#include <bits/stdc++.h>
using namespace std;
using ll=long long;
//矩阵结构体
struct MAT {
    int row,col; //矩阵的行数，列数
    vector<vector<ll>> data; //矩阵
    //矩阵构造
    MAT(int r,int c,ll init=0) {
        row=r,col=c;
        data.assign(r,vector<ll> (c,init));
    }
     
    //矩阵乘法
    MAT operator*(const MAT &other) const {
        assert(col==other.row);
        MAT res(row,other.col,0);
        for(int i=0;i<row;i++) {
            for(int j=0;j<other.col;j++) {
                for(int k=0;k<col;k++) {
                    res.data[i][j]+=data[i][k]*other.data[k][j];
                }
            }
        }
        return res;
    }
};
//生成单位矩阵
MAT IMAT(int n) {
    MAT res(n,n,0);
    for(int i=0;i<n;i++) res.data[i][i]=1;
    return res;
}
//矩阵快速幂
MAT fpow(MAT base,ll exp) {
    MAT res=IMAT(base.row);
    while(exp) {
        if(exp&1) {
            res=res*base;
        }
        base=base*base;
        exp>>=1;
    }
    return res;
}