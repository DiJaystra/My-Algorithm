//给定 n 个整数构成的序列 a，将对于指定的闭区间 [l,r] 查询其区间内的第 k 小值
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//基于值域线段树的主席树
const int MAXN=2e5+5; //数组长度最大值
const int MAXT=MAXN*24; //节点总数最大值
int n,m,s; //数组长度，查询数量，数组中不同数的数量
vector<int> arr(MAXN); //原数组
vector<int> sorted(MAXN); //离散化有序数组
//一个数是第几小
int kth(int x) {
    return lower_bound(sorted.begin()+1,sorted.begin()+s+1,x)-sorted.begin();
}
//版本v的根节点
vector<int> root(MAXN);
//节点i的左右孩子，以及子树大小
vector<int> lch(MAXT),rch(MAXT);
vector<int> siz(MAXT);
int cnt=0; //节点编号分配

//建出0号树（什么都没有）
int build(int l,int r) {
    int now=++cnt;
    siz[now]=0;
    if(l<r) {
        int mid=(l+r)>>1;
        lch[now]=build(l,mid);
        rch[now]=build(mid+1,r);
    }
    return now;
}
//在id号节点增加一个排名为k的数字
int update(int id,int l,int r,int k) {
    int now=++cnt;
    lch[now]=lch[id];
    rch[now]=rch[id];
    siz[now]=siz[id]+1;
    if(l<r) {
        int mid=(l+r)>>1;
        if(k<=mid) lch[now]=update(lch[now],l,mid,k);
        else rch[now]=update(rch[now],mid+1,r,k);
    }
    return now;
}
//查询数组l~r中第k小的数，用线段树版本(l-1)~r作差的技巧
//函数中的l,r是线段树的区间(排名l~r)
int query(int u,int v,int l,int r,int k) {
    if(l==r) return l;
    int lsum=siz[lch[v]]-siz[lch[u]];
    int mid=(l+r)>>1;
    //左子树l~r间包含大于等于k个数
    if(lsum>=k) {
        return query(lch[u],lch[v],l,mid,k);
    }
    //左子树l~r间包含小于k个数
    else {
        return query(rch[u],rch[v],mid+1,r,k-lsum);
    }
}
//初始化n+1棵线段树
void prepare() {
    cnt=0;
    //离散化
    for(int i=1;i<=n;i++) sorted[i]=arr[i];
    sort(sorted.begin()+1,sorted.begin()+n+1);
    s=1;
    for(int i=2;i<=n;i++) {
        if(sorted[s]!=sorted[i]) sorted[++s]=sorted[i];
    }
    //建原树
    root[0]=build(1,s);
    //建出所有树
    for(int i=1;i<=n;i++) {
        int k=kth(arr[i]);
        root[i]=update(root[i-1],1,s,k);
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n>>m;
    for(int i=1;i<=n;i++) cin>>arr[i];
    prepare();
    for(int i=1;i<=m;i++) {
        int l,r,k;cin>>l>>r>>k;
        int ans=query(root[l-1],root[r],1,s,k);
        cout<<sorted[ans]<<'\n';
    }
    return 0;
}
