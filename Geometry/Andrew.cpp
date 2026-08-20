#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ld=long double;

const int MAXN=2e5+5;

int n; //点的数量

//二维平面点结构体
struct point {
    ld x,y;
};
//所有点，凸包点
point P[MAXN],convex[MAXN];
int nc=0; //凸包顶点数量

point sta[MAXN]; //andrew算法辅助栈
int top=0; //栈顶

//计算叉积(pa->pb) x (pa->pc)
ld cross(point pa,point pb,point pc) {
    return (pb.x-pa.x)*(pc.y-pa.y)-(pc.x-pa.x)*(pb.y-pa.y);
}

//计算凸包上的点，逆时针给出
void andrew() {
    //特判点数小于等于2的情况
    if(n<=2) {
        for(int i=1;i<=n;i++) convex[i]=P[i];
        nc=n;
        return;
    }
    //点排序（先按横坐标升序，再按纵坐标升序）
    sort(P+1,P+n+1,[](const point &pa,const point &pb) {
        return pa.x==pb.x ? pa.y<pb.y : pa.x<pb.x;
    });
    //计算下凸包
    for(int i=1;i<=n;i++) {
        while(top>1 && cross(sta[top-1],sta[top],P[i]) <= 0) top--;
        sta[++top]=P[i];
    }
    //计算上凸包
    int t=top;
    for(int i=n-1;i>=1;i--) {
        while(top>t && cross(sta[top-1],sta[top],P[i]) <= 0) top--;
        sta[++top]=P[i];
    }
    //得到答案
    for(int i=1;i<top;i++) convex[i]=sta[i];
    nc=top-1;
}

//扇形二分判断点是否在凸包内部（不包含边界）
bool inside(point p) {
    if(nc<3) return false;
    if(cross(convex[1],convex[2],p)<=0) return false;
    if(cross(convex[nc],convex[1],p)<=0) return false;

    int l=2,r=nc-1,res=2;
    while(l<=r) {
        int mid=(l+r)>>1;
        if(cross(convex[1],convex[mid],p)>0) res=mid,l=mid+1;
        else r=mid-1;
    }

    if(cross(convex[res],convex[res+1],p)<=0) return false;
    return true;
}

signed main() {
    cin>>n;
    for(int i=1;i<=n;i++) cin>>P[i].x>>P[i].y;

    andrew();
    for(int i=1;i<=nc;i++) {
        printf("%Lf %Lf\n",convex[i].x,convex[i].y);
    }

    int q;cin>>q;
    while(q--) {
        double x,y;cin>>x>>y;
        point p={x,y};
        if(inside(p)) cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}
