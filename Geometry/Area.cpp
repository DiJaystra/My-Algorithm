#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;

int MAXN=2e5+5;
int n;

//二维平面点结构体
struct P {
    db x,y;
};

vector<P> point(MAXN); //顶点按逆时针给出

//计算叉积(pa->pb) x (pa->pc)
db cross(P pa,P pb, P pc) {
    return (pb.x-pa.x)*(pc.y-pa.y)-(pc.x-pa.x)*(pb.y-pa.y);
}
//计算多边形面积
db area() {
    if(n<3) return 0;
    db res=0;
    P root=point[1];
    for(int i=2;i<=n-1;i++) res+=cross(root,point[i],point[i+1])/2;
    return res;
}

signed main() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>point[i].x>>point[i].y;
    printf("%lf\n",area());
    return 0;
}
