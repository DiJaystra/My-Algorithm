#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;

//二维平面点结构体
struct P {
    db x,y;
};
//计算叉积(pa->pb) x (pa->pc)
db cross(P pa,P pb, P pc) {
    return (pb.x-pa.x)*(pc.y-pa.y)-(pc.x-pa.x)*(pb.y-pa.y);
}

signed main() {
    P A,B,C;
    cin>>A.x>>A.y>>B.x>>B.y>>C.x>>C.y;
    //三角形面积 = |叉积| / 2
    db ans=fabs(cross(A,B,C))/2;
    printf("%.2lf\n",ans);
    return 0;
}
