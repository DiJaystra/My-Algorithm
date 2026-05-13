#include <bits/stdc++.h>
using namespace std;
using ll=long long;

const int MAXN=1e7+5;
int a[MAXN],lc[MAXN],rc[MAXN],sta[MAXN];
int n;
//基于栈的O(n)建树
void build() {
    int top=0,pos=0;
    for(int i=1;i<=n;i++) {
        pos=top;
        while(pos > 0 && a[sta[pos]] > a[i]) pos--;
        if(pos>0) rc[sta[pos]]=i;
        if(pos<top) lc[i]=sta[pos+1];
        sta[++pos]=i;
        top=pos;
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=1;i<=n;i++) cin>>a[i];
    build();

    ll ans1=0,ans2=0;
    for(int i=1;i<=n;i++) {
        ans1^=1LL*i*(lc[i]+1);
        ans2^=1LL*i*(rc[i]+1);
    }
    cout<<ans1<<' '<<ans2<<'\n';
    return 0;
}