#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;

//二维平面点结构体
struct point {
    ld x,y;
};
//计算叉积(pa->pb) x (pa->pc)
ld cross(point pa,point pb, point pc) {
    return (pb.x-pa.x)*(pc.y-pa.y)-(pc.x-pa.x)*(pb.y-pa.y);
}

signed main() {
    point A,B,C;
    cin>>A.x>>A.y>>B.x>>B.y>>C.x>>C.y;
    //三角形面积 = |叉积| / 2
    ld ans=fabs(cross(A,B,C))/2;
    printf("%.2Lf\n",ans);
    return 0;
}
