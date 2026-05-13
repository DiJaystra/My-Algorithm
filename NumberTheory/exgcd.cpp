#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//求方程ax+by=gcd(a,b)的一个特解
template<typename T>
pair<T,T> exgcd(T a,T b) {
    if(b==0) return {1,0};
    auto [x,y]=exgcd(b,a%b);
    return {y,x-a/b*y};
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    //求方程ax+by=c的一个特解
    int a,b,c;cin>>a>>b>>c;
    int g=__gcd(a,b); //事先调用函数算出gcd
    if(c%g) cout<<"无解\n"; //自己判断有没有解
    else {
        auto [x,y]=exgcd(a,b);
        x*=c/g,y*=c/g; //还原为原方程的一个特解
        cout<<x<<' '<<y<<'\n';
    }
    //要使用到通解？
    //方法：将x0,y0还原为原方程的一个特解后，通解即为：
    //x=x0+(b/g)*t
    //y=y0-(a/g)*t
    return 0;
}