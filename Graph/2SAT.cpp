//Verified SRM464 Div1 550
class SAT {
public:
  static const int MAX_V = 2 << 17;
  vector<int> g[MAX_V], rg[MAX_V], vs;
  bool used[MAX_V];
  int cmp[MAX_V], V, N;

  SAT (int n) : V(2 * n), N(n) {;}

  //(X_2 | !X_5) -> add_closure(2, 1, 5, 0)
  void add_closure(int i, bool bi, int j, bool bj) {
    add_edge(i + N * !bi, j + N * bj);
    add_edge(j + N * !bj, i + N * bi);
  }
  
  void add_edge(int from, int to) {
    g[from].push_back(to);
    rg[to].push_back(from);
  }
  
  void dfs(int v) {
    used[v] = true;
    for (int i : g[v]) if (!used[i]) dfs(i);
    vs.push_back(v);
  }
  
  void rdfs(int v, int k) {
    used[v] = true; cmp[v] = k;
    for (int i : rg[v]) if (!used[i]) rdfs(i, k);
  }

  //no solution: {}, else {1, 0, 1,...}
  vector<bool> solve() {
    memset(used, 0, sizeof(used));
    vs.clear();
    REP(v, V) if (!used[v]) dfs(v);
    memset(used, 0, sizeof(used));
    reverse(ALL(vs));
    int k = 0;
    for (int i : vs) if (!used[i]) rdfs(i, k++);
    vector<bool> res;
    REP(i, N) if (cmp[i] == cmp[i + N]) return res;
    REP(i, N) {
      if (cmp[i] < cmp[N + i]) res.push_back(true);
      else res.push_back(false);
    }
    return res;
  }
};
