#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;

const int MAXN=2e5+5;

int n; //点数

//二维平面点结构体
struct point {
    ld x,y;
};

point P[MAXN]; //顶点按逆时针给出

//计算叉积(pa->pb) x (pa->pc)
ld cross(point pa,point pb,point pc) {
    return (pb.x-pa.x)*(pc.y-pa.y)-(pc.x-pa.x)*(pb.y-pa.y);
}
//计算多边形面积
ld area() {
    if(n<3) return 0;
    ld res=0;
    point root=P[1];
    for(int i=2;i<=n-1;i++) res+=cross(root,P[i],P[i+1])/2;
    return res;
}

signed main() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>P[i].x>>P[i].y;
    printf("%.2Lf\n",area());
    return 0;
}
