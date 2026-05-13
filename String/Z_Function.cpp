#include <bits/stdc++.h>
using namespace std;
using ll=long long;

vector<int> calc_z(const string &s) {
    vector<int> z;
    int n=s.size();
    z.resize(n);
    int l=0,r=0;
    z[0]=n;
    for(int i=1;i<n;i++) {
        if(i<=r) z[i]=min(z[i-l],r-i+1);
        while(i+z[i]<n && s[z[i]] == s[i+z[i]]) z[i]++;
        if(i+z[i]-1 > r) l=i,r=i+z[i]-1;
    }
    return z;
}

signed main() {
    int n;cin>>n;
    string s;cin>>s;
    vector<int> z=calc_z(s);
    for(int i=0;i<n;i++) {
        cout<<z[i]<<' ';
    }
    cout<<'\n';
    return 0;
}