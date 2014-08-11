typedef int Weight;
const Weight INF = 1000000000;
struct Edge{ int src, dest; Weight weight; };
 
typedef vector<Weight> Array;
typedef vector<Array> Matrix;

Weight shortestHamiltonPath(Matrix w, int s) {
  int n = w.size(), N = 1 << n;
  vector<vector<int>> best(N, vector<int>(n));
  REP(v,N) REP(i,n) best[v][i] = INF;
  best[1<<s][s] = 0;
  REP(v,N) REP(i,n) if (v & (1 << i))
    REP(j,n) if (!(v&(1<<j)) && best[v|(1<<j)][j] > best[v][i] + w[i][j])
      best[v|(1<<j)][j] = best[v][i] + w[i][j];
  auto it = best[N-1].begin();
  int t = min_element(it, it + n) - it;
  return best[N-1][t];
}

Weight shortestHamiltonCycle(Matrix w) {
  int n = w.size(), N = 1 << n;
  vector<vector<int>> best(N, vector<int>(n));
  REP(v,N) REP(i,n) best[v][i] = INF;
  best[1][0] = 0;
  REP(v,N) REP(i,n) if (v & (1 << i))
    REP(j,n) if (!(v&(1<<j)) && best[v|(1<<j)][j] > best[v][i] + w[i][j])
        best[v|(1<<j)][j] = best[v][i] + w[i][j];
  int res = INF;
  REP(i,n) res = min(res, best[N-1][i] + w[i][0]);
  return res;
}
