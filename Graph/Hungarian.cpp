Weight hungarian(const Matrix &a) {
  int n = a.size(), p, q;
  Array fx(n, inf), fy(n, 0);
  vector<int> x(n, -1), y(n, -1);
  for (int i = 0; i < n; ) {
    vector<int> t(n, -1), s(n+1, i);
    for (p = q = 0; p <= q && x[i] < 0; ++p)
      for (int k = s[p], j = 0; j < n && x[i] < 0; ++j)
        if (fx[k] + fy[j] == a[k][j] && t[j] < 0) {
          s[++q] = y[j], t[j] = k;
          if (s[q] < 0)
            for (p = j; p >= 0; j = p)
              y[j] = k = t[j], p = x[k], x[k] = j;
        }
    if (x[i] < 0) {
      Weight d = inf;
      for (int k = 0; k <= q; ++k)
        REP(j,n)
          if (t[j] < 0) d = min(d, fx[s[k]] + fy[j] - a[s[k]][j]);
      REP(j,n) fy[j] += (t[j] < 0 ? 0 : d);
      for (int k = 0; k <= q; ++k) fx[s[k]] -= d;
    } else ++i;
  }
  Weight ret = 0;
  REP(i,n) ret += a[i][x[i]];
  return ret;
}
