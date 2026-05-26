#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using db=double;

int MAXN=2e5+5;
int n; //点的数量

//二维平面点结构体
struct P {
    db x,y;
};
//所有点，凸包点
vector<P> point(MAXN),convex(MAXN);
int nc=0; //凸包顶点数量

//对点先按横坐标升序排序，再按纵坐标升序排序
bool cmp(const P &pa,const P &pb) {
    return pa.x==pb.x ? pa.y<pb.y : pa.x<pb.x;
}

//计算叉积(pa->pb) x (pa->pc)
db cross(P pa,P pb, P pc) {
    return (pb.x-pa.x)*(pc.y-pa.y)-(pc.x-pa.x)*(pb.y-pa.y);
}
//计算凸包上的点，逆时针给出
void andrew() {
    if(n<=2) {
        for(int i=1;i<=n;i++) convex[i]=point[i];
        nc=n;
        return;
    }
    //点排序
    sort(point.begin()+1,point.begin()+n+1,cmp);
    vector<P> sta(n+1);
    int top=0;
    //计算下凸包
    for(int i=1;i<=n;i++) {
        while(top>1 && cross(sta[top-1],sta[top],point[i]) <= 0) top--;
        sta[++top]=point[i];
    }
    //计算上凸包
    int t=top;
    for(int i=n-1;i>=1;i--) {
        while(top>t && cross(sta[top-1],sta[top],point[i]) <= 0) top--;
        sta[++top]=point[i];
    }
    //得到答案
    for(int i=1;i<top;i++) convex[i]=sta[i];
    nc=top-1;
}
//判断点是否在凸包内部（不包含边界）
bool in(P p) {
    if(nc<3) return false;
    if(cross(convex[1],convex[2],p)<=0) return false;
    if(cross(convex[nc],convex[1],p)<=0) return false;

    int l=1,r=nc,res=2;
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
    for(int i=1;i<=n;i++) cin>>point[i].x>>point[i].y;

    andrew();
    for(int i=1;i<=nc;i++) {
        printf("%lf %lf\n",convex[i].x,convex[i].y);
    }

    int q;cin>>q;
    while(q--) {
        double x,y;cin>>x>>y;
        P p={x,y};
        if(in(p)) cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}
