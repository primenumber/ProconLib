struct KMP {
  string P;
  vector<int> f;
  KMP (const string &str) {
    P = str;
    int n = P.size(), k = 0;
    f.assign(n, 0);
    f[0] = 0;
    for (int i = 1; i < n; ++i) {
      while (k > 0 && P[k] != P[i]) k = f[k-1];
      if (P[k] == P[i]) ++k;
      f[i] = k;
    }
  }
  vector<int> query(const string &T) {
    int n = P.size(), L = T.size(), k = 0;
    vector<int> res;
    for (int i = 0; i < L; ++i) {
      while (k > 0 && P[k] != T[i]) k = f[k-1];
      if (P[k] == T[i]) ++k;
      if (k == n) {
        res.push_back(i - n + 1);
        k = f[k-1];
      }
    }
    return res;
  }
};
