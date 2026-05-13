#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int MAXN=2e5+5; //最大矩形数量
int n; //矩形数量

//记录矩形位置信息
//0:左下角横坐标，1:左下角纵坐标，2:右上角横坐标，3:右上角纵坐标
vector<vector<ll>> rec(MAXN,vector<ll>(4));

//一个矩形产生两个事件，也就是两条扫描线
vector<vector<ll>> line(MAXN*2,vector<ll>(4));

//对所有横/纵坐标进行离散化
vector<ll> vsort(MAXN*2);
//查找横/纵坐标排名
map<ll,int> vrank;
int nv=0; //vsort有效元素个数

//线段树
int MAXV=16*MAXN; //一定要开16倍长度，因为到达叶子节点未直接return
//维护的三个信息：节点代表的总长度，当前实际覆盖长度，当前覆盖次数
vector<ll> length(MAXV),cover(MAXV);
vector<int> times(MAXV);
//建树（初始化length数组）
void build(int id,int l,int r) {
    if(l==r) {
        length[id]=vsort[l+1]-vsort[l];
        return;
    }
    int mid=(l+r)>>1;
    build(id<<1,l,mid);
    build(id<<1|1,mid+1,r);
    length[id]=length[id<<1]+length[id<<1|1];
}
//汇总信息
void up(int id) {
    if(times[id]>0) cover[id]=length[id];
    else cover[id]=cover[id<<1]+cover[id<<1|1];
}
//区间修改
void update(int id,int l,int r,int ql,int qr,int val) {
    if(ql<=l && r<=qr) {
        times[id]+=val;
    }
    else {
        int mid=(l+r)>>1;
        if(ql<=mid) update(id<<1,l,mid,ql,qr,val);
        if(qr>mid) update(id<<1|1,mid+1,r,ql,qr,val);
    }
    up(id);
}

//处理line数组，对y进行离散化
void prepareY() {
    //读取事件
    for(int i=1,j=1+n;i<=n;i++,j++) {
        line[i][0]=rec[i][0];
        line[i][1]=rec[i][1];
        line[i][2]=rec[i][3];
        line[i][3]=1;

        line[j][0]=rec[i][2];
        line[j][1]=rec[i][1];
        line[j][2]=rec[i][3];
        line[j][3]=-1;

        vsort[i]=rec[i][1];
        vsort[j]=rec[i][3];
    }
    //对y进行排序
    sort(vsort.begin()+1,vsort.begin()+2*n+1);
    //对y去重
    int now=1;
    for(int i=2;i<=2*n;i++) {
        if(vsort[i]!=vsort[i-1]) vsort[++now]=vsort[i];
    }
    vsort[now+1]=vsort[now];
    nv=now;
    //预处理所有纵坐标的排名
    vrank.clear();
    for(int i=1;i<=nv;i++) {
        vrank[vsort[i]]=i;
    }

    //将line数组的纵坐标变为排名
    for(int i=1;i<=2*n;i++) {
        line[i][1]=vrank[line[i][1]];
        line[i][2]=vrank[line[i][2]];
    }
    //对任务按横坐标排序（一定要先+再-，否则重复贡献2次）
    sort(line.begin()+1,line.begin()+2*n+1,
    [](vector<ll> x,vector<ll> y){
        if(x[0]==y[0]) return x[3]>y[3];
        return x[0]<y[0];
    });
}

//处理line数组，对x进行离散化
void prepareX() {
    //读取事件
    for(int i=1,j=1+n;i<=n;i++,j++) {
        line[i][0]=rec[i][1];
        line[i][1]=rec[i][0];
        line[i][2]=rec[i][2];
        line[i][3]=1;

        line[j][0]=rec[i][3];
        line[j][1]=rec[i][0];
        line[j][2]=rec[i][2];
        line[j][3]=-1;

        vsort[i]=rec[i][0];
        vsort[j]=rec[i][2];
    }
    //对x进行排序
    sort(vsort.begin()+1,vsort.begin()+2*n+1);
    //对x去重
    int now=1;
    for(int i=2;i<=2*n;i++) {
        if(vsort[i]!=vsort[i-1]) vsort[++now]=vsort[i];
    }
    vsort[now+1]=vsort[now];
    nv=now;
    //预处理所有横坐标的排名
    vrank.clear();
    for(int i=1;i<=nv;i++) {
        vrank[vsort[i]]=i;
    }

    //将line数组的横坐标变为排名
    for(int i=1;i<=2*n;i++) {
        line[i][1]=vrank[line[i][1]];
        line[i][2]=vrank[line[i][2]];
    }
    //对任务按纵坐标排序（一定要先+再-，否则重复贡献2次）
    sort(line.begin()+1,line.begin()+2*n+1,
    [](vector<ll> x,vector<ll> y){
        if(x[0]==y[0]) return x[3]>y[3];
        return x[0]<y[0];
    });
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1,j=1+n;i<=n;i++,j++) { //输入矩形
        cin>>rec[i][0]>>rec[i][1]>>rec[i][2]>>rec[i][3];
    }
    //先贡献y的边长
    prepareY();
    build(1,1,nv);
    ll ans=0;
    for(int i=1;i<=2*n;i++) {
        ll pre=cover[1];
        update(1,1,nv,line[i][1],line[i][2]-1,line[i][3]);
        ll now=cover[1];
        //差值的绝对值作为贡献
        ans+=abs(now-pre);
    }
    //再贡献x的边长
    prepareX();
    build(1,1,nv);
    for(int i=1;i<=2*n;i++) {
        ll pre=cover[1];
        update(1,1,nv,line[i][1],line[i][2]-1,line[i][3]);
        ll now=cover[1];
        ans+=abs(now-pre);
    }
    cout<<ans<<'\n';
    return 0;
}
