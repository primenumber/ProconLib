typedef int Weight;
Weight INF = 1000000000;
typedef vector<Weight> Array;
typedef vector<Array> Matrix;

// StoerWagner (Verified: POJ2914)
Weight global_minimum_cut(Matrix h) {
  int N = h.size();
  vector<int> V(N); REP(u, N) V[u] = u;
  Weight cut = INF;
  for(int m = N; m > 1; m--) {
    vector<Weight> ws(m, 0);
    int u, v = -1;
    Weight w;
    REP(k, m) {
      u = v;
      v = max_element(ws.begin(), ws.end()) - ws.begin();
      w = ws[v];
      ws[v] = -1;
      REP(i, m) if (ws[i] >= 0) ws[i] += h[V[v]][V[i]];
    }
    REP(i, m) {
      h[V[i]][V[u]] += h[V[i]][V[v]];
      h[V[u]][V[i]] += h[V[v]][V[i]];
    }
    V.erase(V.begin() + v);
    cut = min(cut, w);
  }
  return cut;
}
