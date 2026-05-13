#include <bits/stdc++.h>
using namespace std;
using ll=long long;
using ull=unsigned long long;
using ld=long double;
using lll=__int128;

int n;

vector<int> a,b; //a为需排序数组，b为辅助数组（记得assign）
ll inv; //逆序对计数（记得初始化为0）
//归并排序同时计算逆序对，O(nlogn)
void mergeSort(int l,int r) {
    if(l>=r) return;
    int mid=(l+r)>>1;
    mergeSort(l,mid);
    mergeSort(mid+1,r);

    //归并排序的模板
    int p1=l,p2=mid+1,p=l;
    while(p1<=mid && p2<=r) {
        if(a[p1]<=a[p2]) b[p++]=a[p1++];
        else b[p++]=a[p2++],inv+=mid-p1+1LL; //取右边的数则形成逆序对
    }
    while(p1<=mid) b[p++]=a[p1++];
    while(p2<=r) b[p++]=a[p2++];

    for(int i=l;i<=r;i++) {
        a[i]=b[i];
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);

    cin>>n;
    a.assign(n,0),b.assign(n,0);
    for(int i=0;i<n;i++) cin>>a[i];

    inv=0;
    mergeSort(0,n-1);
    cout<<inv<<'\n';

    return 0;
}