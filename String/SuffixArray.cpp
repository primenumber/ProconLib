struct SuffixArray {
  const int MAXLG = 18;
  int N, s;
  vector<tuple<int,int,int>> L;
  vector<int> inv;
  vector<string> P;

  SuffixArray(string A) {
    N = A.size(); s = 1;
    L.assign(N, make_tuple(0, 0, 0));
    inv.assign(N, 0);
    P.assign(MAXLG, string(N, ' ')); P[0] = A;
    for (int c = 1; c < N; ++s, c <<= 1) {
      REP(i,N) L[i] = make_tuple(P[s-1][i], (i+c<N ? P[s-1][i+c] : -1), i);
      sort(ALL(L));
      REP(i,N) {
        int u, v, w, x, y, z; tie(u, v, w) = L[i-1]; tie(x, y, z) = L[i];
        if (i > 0 && x == u && y == v) P[s][z] = P[s][w]; else P[s][z] = i;
      }
    }
    REP(i,N) inv[P[s-1][i]] = i;
  }

  int lcp(int x, int y){
    if (x == y) return N - x;
    int ret = 0;
    for (int k = s-1; k >= 0 && x < N && y < N; --k)
      if(P[k][x] == P[k][y]) x += (1 << k), y += (1 << k), ret |= (1 << k);
    return ret;
  }
};
