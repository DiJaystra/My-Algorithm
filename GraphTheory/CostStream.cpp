#include <bits/stdc++.h>
using namespace std;

template<typename Cap, typename Cost>
struct MinCostFlow {
    struct Edge {
        int to;
        Cap cap;
        Cost cost;
        int rev;
    };
    
    int n;
    vector<vector<Edge>> graph;
    vector<Cost> dist;
    vector<int> prevv, preve;
    const Cost INF = numeric_limits<Cost>::max() / 2;
    
    MinCostFlow(int n) : n(n), graph(n), dist(n), prevv(n), preve(n) {}
    
    void add_edge(int from, int to, Cap cap, Cost cost) {
        graph[from].push_back({to, cap, cost, (int)graph[to].size()});
        graph[to].push_back({from, 0, -cost, (int)graph[from].size() - 1});
    }
    
    pair<Cap, Cost> flow(int s, int t, Cap flow_limit = numeric_limits<Cap>::max()) {
        Cap total_flow = 0;
        Cost total_cost = 0;
        
        while (flow_limit > 0) {
            fill(dist.begin(), dist.end(), INF);
            dist[s] = 0;
            
            bool update = true;
            while (update) {
                update = false;
                for (int v = 0; v < n; v++) {
                    if (dist[v] == INF) continue;
                    for (int i = 0; i < graph[v].size(); i++) {
                        Edge &e = graph[v][i];
                        if (e.cap > 0 && dist[e.to] > dist[v] + e.cost) {
                            dist[e.to] = dist[v] + e.cost;
                            prevv[e.to] = v;
                            preve[e.to] = i;
                            update = true;
                        }
                    }
                }
            }
            
            if (dist[t] == INF) break;
            
            Cap f = flow_limit;
            for (int v = t; v != s; v = prevv[v]) {
                f = min(f, graph[prevv[v]][preve[v]].cap);
            }
            
            flow_limit -= f;
            total_flow += f;
            total_cost += f * dist[t];
            
            for (int v = t; v != s; v = prevv[v]) {
                Edge &e = graph[prevv[v]][preve[v]];
                e.cap -= f;
                graph[v][e.rev].cap += f;
            }
        }
        
        return {total_flow, total_cost};
    }
};

/*
初始化：MinCostFlow<CapacityType, CostType> graph(node_count);

添加边：graph.add_edge(from, to, capacity, cost);

计算最小费用最大流：auto [flow, cost] = graph.flow(source, sink);

限制流量：auto [flow, cost] = graph.flow(source, sink, flow_limit);
（计算最多flow_limit流量的最小费用流）
*/