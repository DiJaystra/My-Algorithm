#include <bits/stdc++.h>
using namespace std;
using ll=long long;

int MAXN=2e5+5;
int n;
vector<ll> arr(MAXN); //原数组
vector<ll> sorted1(MAXN); //排序数组1
vector<ll> sorted2(MAXN); //排序数组2

vector<ll> heap(MAXN); //堆
int heap_size=0; //堆的有效大小
//向上调整堆
void heapUp(int idx) {
    int fa=(idx-1)/2;
    while(heap[idx] > heap[fa]) {
        swap(heap[idx],heap[fa]);
        idx=fa,fa=(idx-1)/2;
    }
}
//向下调整堆
void heapDown(int idx) {
    int lch=idx*2+1;
    while(lch < heap_size) {
        int best = lch+1 < heap_size && heap[lch+1] > heap[lch] ? lch+1 : lch;
        best = heap[best] > heap[idx] ? best : idx;
        if(best==idx) break;
        swap(heap[best],heap[idx]);
        idx=best;
        lch=idx*2+1;
    }
}
//自顶向下建立大根堆，时间复杂度O(n*log n)
//依次弹出最大值，时间复杂度:O(n*log n)
void heapSort1() {
    heap_size=0;
    while(heap_size < n) {
        heap[heap_size]=arr[heap_size];
        heapUp(heap_size++);
    }
    while(heap_size) {
        sorted1[heap_size-1]=heap[0];
        swap(heap[0],heap[--heap_size]);
        heapDown(0);
    }
}
//自底向上建立大根堆，时间复杂度:O(n)
//依次弹出最大值，时间复杂度:O(n*log n)
void heapSort2() {
    for(int i=0;i<n;i++) heap[i]=arr[i];
    heap_size=n;
    for(int i=n-1;i>=0;i--) heapDown(i);
    while(heap_size) {
        sorted2[heap_size-1]=heap[0];
        swap(heap[0],heap[--heap_size]);
        heapDown(0);
    }
}

signed main() {
    ios::sync_with_stdio(false);cin.tie(0);
    cin>>n;
    for(int i=0;i<n;i++) cin>>arr[i];
    heapSort1();
    for(int i=0;i<n;i++) cout<<sorted1[i]<<' ';
    cout<<'\n';
    heapSort2();
    for(int i=0;i<n;i++) cout<<sorted2[i]<<' ';
    cout<<'\n';
    return 0;
}