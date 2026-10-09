#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;

const int MAXN=1e3+5; //多项式最大次数

int n; //多项式次数
pair<ld,ld> p[MAXN]; //多项式过的点

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>p[i].first>>p[i].second;

    ld x0;cin>>x0; //查询的横坐标
    ld ans=0;
    //按照公式计算
    for(int i=1;i<=n;i++) {
        auto [xi,yi]=p[i];
        ld Li=1;
        for(int j=1;j<=n;j++) {
            auto [xj,yj]=p[j];
            if(j!=i) {
                Li*=(x0-xj)/(xi-xj);
            }
        }
        ans+=yi*Li;
    }
    cout<<ans<<'\n';
    return 0;
}