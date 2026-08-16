//普通消元求解异或空间线性基（不一定标准）
//查询原数组生成的异或集合中最大的数
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=55; //最大数字个数
const int BIT=55; //数字最大位数

int n; //数字个数
ll arr[MAXN]; //数字
ll base[BIT]; //线性基

//求解线性基
void getBase() {
    //对于每一个元素
    for(int i=1;i<=n;i++) {
        //考察每一位
        for(int j=BIT-1;j>=0;j--) {
            //若第j位是1
            if((arr[i]>>j)&1) {
                //判断第j位是否有基
                if(base[j]==0) {
                    //如果第j位无基
                    //此数作为第j位的基
                    base[j]=arr[i];
                    break;
                }
                else {
                    //如果该位有基
                    //此数被第j位的基异或，使其第j位变为0
                    arr[i]^=base[j];
                }
            }
        }
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>arr[i];

    getBase();

    ll ans=0;
    //从高位向低位考察每个基
    for(int i=BIT-1;i>=0;i--) {
        //异或还是不异或，不断取最大值
        ans=max(ans,ans^base[i]);
    }
    cout<<ans<<'\n';
    return 0;
}
