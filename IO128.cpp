#include <bits/stdc++.h>
using namespace std;
using lll=__int128;

#ifdef _WIN32
#define getchar_unlocked _getchar_nolock
#endif

lll read() {
	lll k=0;
    int f=1;
    char c=getchar_unlocked();
    while(!isdigit(c)) {
        if(c=='-') f=-1;
        c=getchar_unlocked();
    }

    while(isdigit(c)) {
        k*=10;
        if(f==1) k+=c-'0';
        else k-=c-'0';
        c=getchar_unlocked();
    }
	return k;
}

void write(lll x) {
    if(x==0) {
        puts("0");
        return;
    }
    if(x<0) putchar('-');
    
    vector<char> digit;
    while(x) {
        int num=x%10;
        num=abs(num);
        digit.push_back(num+'0');
        x/=10;
    }
    for(int i=(int)digit.size()-1;i>=0;i--) {
        putchar(digit[i]);
    }
    putchar('\n');
}

signed main() {
	lll n=read();
    write(n);
}
