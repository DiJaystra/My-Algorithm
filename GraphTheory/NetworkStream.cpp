#include <bits/stdc++.h>
using namespace std;

template<typename T>
class MaxFlow {
    struct Edge {
        int to, rev;
        T cap;
        Edge(int t, T c, int r) : to(t), cap(c), rev(r) {}
    };
    
    int n;
    vector<vector<Edge>> graph;
    vector<int> level, iter;
    
public:
    // 初始化，节点数从0到n-1
    MaxFlow(int n) : n(n), graph(n), level(n), iter(n) {}
    
    // 添加边：从u到v，容量为cap
    void add_edge(int u, int v, T cap) {
        graph[u].emplace_back(v, cap, graph[v].size());
        graph[v].emplace_back(u, 0, graph[u].size() - 1);
    }
    
    // BFS构建分层图
    void bfs(int s) {
        fill(level.begin(), level.end(), -1);
        queue<int> q;
        level[s] = 0;
        q.push(s);
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (const auto& e : graph[u]) {
                if (e.cap > 0 && level[e.to] < 0) {
                    level[e.to] = level[u] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    
    // DFS寻找增广路
    T dfs(int u, int t, T f) {
        if (u == t) return f;
        
        for (int& i = iter[u]; i < graph[u].size(); i++) {
            Edge& e = graph[u][i];
            if (e.cap > 0 && level[u] < level[e.to]) {
                T d = dfs(e.to, t, min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    graph[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
    
    // 计算从s到t的最大流
    T max_flow(int s, int t) {
        T flow = 0;
        while (true) {
            bfs(s);
            if (level[t] < 0) return flow;
            fill(iter.begin(), iter.end(), 0);
            T f;
            while ((f = dfs(s, t, numeric_limits<T>::max())) > 0) {
                flow += f;
            }
        }
    }
    
    // 获取残量网络中从s可达的节点（用于最小割）
    vector<bool> min_cut(int s) {
        vector<bool> visited(n, false);
        queue<int> q;
        q.push(s);
        visited[s] = true;
        
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (const auto& e : graph[u]) {
                if (e.cap > 0 && !visited[e.to]) {
                    visited[e.to] = true;
                    q.push(e.to);
                }
            }
        }
        return visited;
    }
    
    // 获取边的流量（正向边的容量减少量）
    T get_flow(int u, int edge_index) {
        if (edge_index >= graph[u].size()) return 0;
        const Edge& e = graph[u][edge_index];
        return graph[e.to][e.rev].cap; // 反向边的容量就是正向边的流量
    }
};

// 示例2：使用long long类型处理大容量
void example_long_long() {
    MaxFlow<long long> mf(3);
    
    // 大容量边
    mf.add_edge(0, 1, 1000000000000LL);
    mf.add_edge(1, 2, 1000000000000LL);
    
    long long flow = mf.max_flow(0, 2);
    cout << "最大流 (long long): " << flow << endl;  // 输出: 1000000000000
}