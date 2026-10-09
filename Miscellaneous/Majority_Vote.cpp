/*
有n张卡片，编号从1到n，每张卡片上写了数字，但你不知道任何一张卡片的数字
你的目标是找到某个数字，其在卡片上的出现次数超过n/2
如果有这样的数字，输出其所属的其中一张卡片的编号
如果没有，输出-1
每次你可以向测评机询问某两张卡片的数字是否相同
测评机返回结果，1表示相同，0表示不同
你需要在不超过2n次询问下得出答案
*/

#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int n; //卡片数量

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;

    //当前候选的卡片编号、当前候选的血量
    int cand=0,hp=0;
    for(int i=1;i<=n;i++) {
        if(hp==0) { //没有候选
            cand=i;
            hp=1;
        }
        else { //有候选
            cout<<"? "<<cand<<' '<<i<<endl;
            int res;cin>>res;
            //与当前卡片i的数字相同
            if(res==1) hp++;
            //与当前卡片i的数字不同
            else hp--;
        }
    }

    //已经没有候选，一定没有水王数
    if(hp==0) {
        cout<<"! -1"<<endl;
        return 0;
    }

    //有候选，hp归为1进行计数
    hp=1;
    for(int i=1;i<=n;i++) {
        if(i!=cand) {
            cout<<"? "<<cand<<' '<<i<<endl;
            int res;cin>>res;
            //当前卡片与候选卡片的值相同
            if(res==1) hp++;
        }
    }

    //候选卡片出现次数超过一半
    if(hp*2>n) cout<<"! "<<cand<<endl;
    //反之一定没有水王数
    else cout<<"! -1"<<endl;
    return 0;
}
