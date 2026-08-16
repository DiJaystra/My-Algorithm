//高斯消元求解异或空间线性标准基
//查询原数组生成的异或集合中，第k小的数
//获取标准基一定要用高斯消元来求
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=1e5+5; //最大数字个数
const int BIT=55; //数字最大位数

int n; //数字个数
int q; //查询数量

ll mat[MAXN]; //数字
int len=0; //基的个数
bool zero=false; //原数字集合能否生成0

//高斯消元求解标准基
void gauss() {
    //从高位向低位遍历
    for(int i=BIT-1;i>=0;i--) {
        //枚举未被定为基的数
        for(int j=len+1;j<=n;j++) {
            //第j个数的第i位是1，则把它拉来做标准基
            if((mat[j]>>i)&1) {
                swap(mat[len+1],mat[j]);
                break;
            }
        }
        //如果真的有某个数在该位是1
        if((mat[len+1]>>i)&1) {
            //给其它数的该位消为0
            for(int j=1;j<=n;j++) {
                if(j!=len+1 && ((mat[j]>>i)&1)) {
                    mat[j]^=mat[len+1];
                }
            }
            //基个数+1
            len++;
        }
    }
    //基的数量小于初始集合大小
    //则原集合一定能拼出0
    if(len<n) zero=true;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>mat[i];

    gauss();

    cin>>q;
    for(int i=1;i<=q;i++) {
        ll k;cin>>k; //查询第k小
        //特判原数组能拼出0的情况
        if(zero) {
            //第一小一定是0
            if(k==1) {
                cout<<"0\n";
                continue;
            }
            //不是第一小，那就是去掉0之后找第k-1小
            else {
                k--;
            }
        }
        //如果k超过了当前集合大小2^len-1
        if(k>=1LL<<len) {
            cout<<"-1\n";
            continue;
        }
        //把k拆成二进制来看
        ll ans=0;
        for(int j=BIT-1;j>=0;j--) {
            //第j位是1，那就让第len-j个标准基参与异或
            if((k>>j)&1) {
                ans^=mat[len-j];
            }
        }
        cout<<ans<<'\n';
    }
    return 0;
}
