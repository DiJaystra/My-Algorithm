//替罪羊树模板
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const double ALPHA=0.7; //平衡因子，最好设成0.7
int MAXN=1e5+5; //空间最大使用量

int head=0; //整棵树的头结点编号
int cnt=0; //空间使用计数
vector<int> key(MAXN); //节点的键值
vector<int> same(MAXN); //节点重复加入的次数
vector<int> lch(MAXN); //节点的左孩子
vector<int> rch(MAXN); //节点的右孩子
vector<int> diff(MAXN); //节点对应的子树（包括自己）有多少个节点
vector<int> siz(MAXN); //节点对应的子树（包括自己）有多少个数字

vector<int> collect(MAXN); //中序遍历收集的节点
int ci; //中序遍历收集的总节点数
int top; //最上方的不平衡节点
int father; //top的父亲（top为head时则为0）
int side; //top是父亲节点的什么孩子，1代表左孩子，2代表右孩子

//新建一个节点
int init(int num) {
    key[++cnt]=num;
    lch[cnt]=rch[cnt]=0;
    same[cnt]=diff[cnt]=siz[cnt]=1;
    return cnt;
}
//汇总信息
void up(int x) {
    siz[x]=siz[lch[x]]+siz[rch[x]]+same[x];
    //由于删除操作，same[x]可能为0，在重建时去除该节点
    diff[x]=diff[lch[x]]+diff[rch[x]]+(same[x]>0 ? 1 : 0);
}
//中序遍历子树x
void inorder(int x) {
    if(x==0) return;
    inorder(lch[x]);
    if(same[x] > 0) { //由于删除操作，same[x]可能为0，去除该节点
        collect[++ci]=x;
    }
    inorder(rch[x]);
}
//以二分的方式重建子树
int rebuild(int l,int r) {
    if(l>r) return 0;
    int mid=(l+r)>>1;
    int h=collect[mid];
    lch[h]=rebuild(l,mid-1);
    rch[h]=rebuild(mid+1,r);
    up(h);
    return h; //返回子树的根节点
}
//判断是否要重建子树
void check() {
    if(top==0) return; //无不平衡节点，不用重建
    ci=0;
    inorder(top);
    if(ci==0) return; //不平衡节点的子树，所有节点都被erase
    if(father==0) { //top==head
        head=rebuild(1,ci);
    }
    else if(side==1) {
        lch[father]=rebuild(1,ci);
    }
    else if(side==2) {
        rch[father]=rebuild(1,ci);
    }
}
//判断子树是否平衡
bool balance(int x) {
    return max(diff[lch[x]],diff[rch[x]]) <= ALPHA*diff[x];
}
//加入数字num
//参数含义：当前节点编号，当前节点的父亲节点编号，x是fa的什么孩子，要加入的数据
void add(int x,int fa,int s,int num) {
    if(x==0) {
        if(fa==0) head=init(num);
        else if(s==1) lch[fa]=init(num);
        else rch[fa]=init(num);
    }
    else {
        if(key[x]==num) same[x]++;
        else if(key[x] > num) add(lch[x],x,1,num);
        else add(rch[x],x,2,num);
    }
    up(x);
    if(!balance(x)) {
        top=x;
        father=fa;
        side=s;
    }
}
//加入方法的接口
void add(int num) {
    top=father=side=0;
    add(head,0,0,num);
    check();
}
//x的子树中，有几个数比num小
int smaller(int x,int num) {
    if(x==0) return 0;
    if(key[x]>=num) return smaller(lch[x],num);
    else return siz[lch[x]]+same[x]+smaller(rch[x],num);
}
//num在所有数中排第几小
int ranking(int num) {
    return smaller(head,num)+1; //排(小于它的所有数+1)名
}
//加入的所有数中，第x名是什么数
int index(int x,int rk) {
    if(x==0) return INT_MAX; //不合法情况
    if(siz[lch[x]]>=rk) return index(lch[x],rk);
    else if(siz[lch[x]]+same[x]<rk) return index(rch[x],rk-(siz[lch[x]]+same[x]));
    return key[x];
}
//查询数字num的前驱
int pre(int num) {
    int kth=ranking(num);
    if(kth==1) return INT_MIN;
    else return index(head,kth-1);
}
//查询数字num的后继
int post(int num) {
    int kth=ranking(num+1);
    if(kth==siz[head]+1) return INT_MAX;
    else return index(head,kth);
}
//删除数字num一个词频
//参数含义：当前节点编号，当前节点的父亲节点编号，x是fa的什么孩子，要删除的数据
void erase(int x,int fa,int s,int num) {
    if(key[x]==num) same[x]--;
    else if(key[x]>num) erase(lch[x],x,1,num);
    else erase(rch[x],x,2,num);
    up(x);
    if(!balance(x)) {
        top=x;
        father=fa;
        side=s;
    }
}
//删除方法的接口
void erase(int num) {
    if(smaller(head,num)!=smaller(head,num+1)) {
        top=father=side=0;
        erase(head,0,0,num);
        check();
    }
}
//清空平衡树
void clear() {
    for(int i=1;i<=cnt;i++) {
        key[i]=same[i]=lch[i]=rch[i]=diff[i]=siz[i]=0;
    }
    cnt=0;
    head=0;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    int q;cin>>q;
    while(q--) {
        int op,x;cin>>op>>x;
        if(op==1) add(x);
        else if(op==2) erase(x);
        else if(op==3) cout<<ranking(x)<<'\n';
        else if(op==4) cout<<index(head,x)<<'\n';
        else if(op==5) cout<<pre(x)<<'\n';
        else cout<<post(x)<<'\n';
    }
    return 0;
}