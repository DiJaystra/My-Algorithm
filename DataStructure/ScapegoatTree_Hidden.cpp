//替罪羊树隐式模板
//也就是无键值的替罪羊树
//插入和删除时，按照指定排名来进行插入删除操作
#include <bits/stdc++.h>
using namespace std;
using ll=long long;

//平衡因子，通常设成0.7
//越小重构越频繁，树高越矮
//越大重构越少，树高越高
const double ALPHA=0.7;
//空间最大使用量
const int MAXN=1e5+5;

int q; //查询数量

int head=0; //整棵树的头结点编号
int cnt=0; //空间使用计数
int lch[MAXN]; //节点的左孩子
int rch[MAXN]; //节点的右孩子
int siz[MAXN]; //节点子树大小
int val[MAXN]; //节点存的信息
bool deleted[MAXN]; //节点是否被删除

int collect[MAXN]; //中序遍历收集的节点
int ci; //中序遍历收集的总节点数
int top; //最上方的不平衡节点
int father; //top的父亲（top为head时则为0）
int side; //top是父亲节点的什么孩子，1代表左孩子，2代表右孩子

//新建一个节点
int init(int num) {
    cnt++;
    lch[cnt]=rch[cnt]=0;
    siz[cnt]=1;
    val[cnt]=num;
    return cnt;
}
//汇总信息
void up(int x) {
    //删除操作会产生墓碑节点，不算在有效节点内
    siz[x]=siz[lch[x]]+siz[rch[x]]+(deleted[x]==false);
}
//中序遍历x这棵子树，收集节点
void inorder(int x) {
    if(x==0) return;
    inorder(lch[x]);
    //删除操作会产生墓碑节点，在此时去除
    if(!deleted[x]) {
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
    return max(siz[lch[x]],siz[rch[x]]) <= ALPHA*siz[x];
}
//插入数字num到第rank名的位置
//参数：节点编号、节点父亲、节点在父亲的哪边、插入的位置排名、插入的值
void add(int x,int fa,int s,int rank,int num) {
    if(x==0) {
        if(fa==0) head=init(num);
        else if(s==1) lch[fa]=init(num);
        else rch[fa]=init(num);
        return;
    }

    //特别注意：rank==siz[lch[x]]+1时插在左树最右侧
    //进入左树的判断与当前节点是否为墓碑节点无关
    if(rank<=siz[lch[x]]+1) {
        add(lch[x],x,1,rank,num);
    }
    else {
        //注意墓碑节点不能算在rank里面
        int self=!deleted[x];
        add(rch[x],x,2,rank-(siz[lch[x]]+self),num);
    }

    up(x);
    if(!balance(x)) {
        top=x;
        father=fa;
        side=s;
    }
}
//插入方法的接口，在rank位置插入num这个值
void add(int rank,int num) {
    //先判断能插入到第rank名，再插入
    if(rank>=1 && rank<=siz[head]+1) {
        top=father=side=0;
        add(head,0,0,rank,num);
        check();
    }
}
//将第rank名的节点信息改为num
//参数：节点编号、修改的位置排名、修改的值
void update(int x,int rank,int num) {
    //当前节点是否为墓碑节点
    int self=!deleted[x];
    //只有当前节点有效才有可能成为修改对象
    if(self && rank==siz[lch[x]]+1) {
        val[x]=num;
    }
    //进入左树的判断
    else if(rank<=siz[lch[x]]) {
        update(lch[x],rank,num);
    }
    else {
        //注意墓碑节点不能算在rank里面
        update(rch[x],rank-(siz[lch[x]]+self),num);
    }
}
//更新方法的接口，把第rank名的节点信息改为num
void update(int rank,int num) {
    //先判断有第rank名，再改
    if(rank>=1 && rank<=siz[head]) {
        update(head,rank,num);
    }
}
//查询x的子树中，排名为rank的节点信息
int index(int x,int rank) {
    //当前节点是否为墓碑节点
    int self=!deleted[x];
    //只有当前节点有效才有可能成为查询对象
    if(self && rank==siz[lch[x]]+1) {
        return val[x];
    }
    //进入左树的判断
    else if(rank<=siz[lch[x]]) {
        return index(lch[x],rank);
    }
    else {
        //注意墓碑节点不能算在rank里面
        return index(rch[x],rank-(siz[lch[x]]+self));
    }
}
//由排名查询值的方法接口
int index(int rank) {
    //如果不存在这个排名，返回-1
    if(rank<1||rank>siz[head]) return -1;
    return index(head,rank);
}
//删除第rank名的数字
//参数：节点编号、节点父亲、节点在父亲的哪边、要删除的位置
void erase(int x,int fa,int s,int rank) {
    int self=!deleted[x];
    //只有当前节点有效才有可能成为擦除对象
    if(self && rank==siz[lch[x]]+1) {
        deleted[x]=true;
    }
    //进入左树的判断
    else if(rank<=siz[lch[x]]) {
        erase(lch[x],x,1,rank);
    }
    else {
        //注意墓碑节点不能算在rank里面
        erase(rch[x],x,2,rank-(siz[lch[x]]+self));
    }

    up(x);
    if(!balance(x)) {
        top=x;
        father=fa;
        side=s;
    }
}
//删除方法的接口，删除第rank名的数字
void erase(int rank) {
    //先判断有第rank名，再删除
    if(rank>=1 && rank<=siz[head]) {
        top=father=side=0;
        erase(head,0,0,rank);
        check();
    }
}
//清空平衡树
void clear() {
    for(int i=1;i<=cnt;i++) {
        lch[i]=rch[i]=siz[i]=val[i]=0;
        deleted[i]=false;
    }
    cnt=0;
    head=0;
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>q;
    for(int i=1;i<=q;i++) {
        int op;cin>>op;
        if(op==1) { //在rank位置添加数字x
            int rank,x;cin>>rank>>x;
            add(rank,x);
        }
        else if(op==2) { //删除第rank位的数字
            int rank;cin>>rank;
            erase(rank);
        }
        else if(op==3) { //查询第rank位的数字
            int rank;cin>>rank;
            cout<<index(rank)<<'\n';
        }
        else if(op==4) { //改第rank位的数字为x
            int rank,x;cin>>rank>>x;
            update(rank,x);
        }
    }
    return 0;
}