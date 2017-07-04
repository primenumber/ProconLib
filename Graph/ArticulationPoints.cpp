#include <vector>
#include <set>

using Weight = int;
struct Edge{
  int src, dest;
  bool operator < (const Edge &rhs) const {
    return make_pair(src, dest) < make_pair(rhs.src, rhs.dest);
  }
};

using Edges = vector<Edge>;
using Graph = vector<Edges>;

set<int> art;
vector<set<Edge> > connect;
vector<Edge> st;
vector<int> order, low;
int cnt;

void artDfs(const Graph &g, int from, int parent) {
  low[from] = order[from] = cnt++;
  for (Edge e : g[from]) {
    int to = e.dest;
    if (to != parent && order[to] < order[from]) st.push_back(e);
    if (order[to] == -1) {
      artDfs(g, to, from);
      low[from] = min(low[from], low[to]);
      if ((order[from] == 0 && order[to] != 1) || (order[from] != 0 && low[to] >= order[from]))
        art.insert(from);
      if (low[to] >= order[from]) {
        connect.push_back(set<Edge>());
        while (true) {
          Edge edge = st.back();
          st.pop_back();
          connect.back().insert(edge);
          if (edge.src == from && edge.dest == to) break;
        }
      }
    }
    else {
      low[from] = min(low[from], order[to]);
    }
  }
}

set<int> articulationPoints(const Graph &g) {
  const int n = g.size();
  art.clear(); connect.clear(); st.clear();
  order.assign(n, -1); low.assign(n, -1);
  for (int i = 0; i < n; i++) {
    if (order[i] != -1) continue;
    cnt = 0;
    artDfs(g, i, i);
  }
  return art;
}
