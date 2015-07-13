// verified : TDPC T
// a_n = sum c_i a_n-k+i
// O(K^2 logN)

vector<Mod> convolution(const vector<Mod> &lhs, const vector<Mod> &rhs) {
  int n = lhs.size(), m = rhs.size();
  vector<Mod> res(n + m);
  REP(i,n) REP(j,m) res[i+j] += lhs[i] * rhs[j];
  return res;
}

vector<Mod> km_sub(const vector<int> &c1, const vector<Mod> &c2, int K, ll N) {
  vector<Mod> res(K);
  if (N < K) res[N] = Mod(1);
  else if (N % 2 == 0) {
    res = km_sub(c1, c2, K, N/2);
    res = convolution(res, res);
    REP(i,K) REP(j,c1.size()) res[K-i+c1[j]-1] += c2[j] * res[2*K-i-1];
    res.resize(K);
  }
  else {
    res = km_sub(c1, c2, K, N-1);
    Mod carry = res[K-1];
    REP(i,K-1) res[K-i-1] = res[K-i-2];
    res[0] = Mod(0);
    REP(i,c1.size()) res[c1[i]] += c2[i] * carry;
  }
  return res;
}

Mod kita_masa(const vector<Mod> &c, const vector<Mod> &a, ll N) {
  assert(c.size() == a.size());
  int K = c.size();
  vector<int> c1; vector<Mod> c2;
  REP(i,K) if (c[i].num) { c1.push_back(i); c2.push_back(c[i]); }
  vector<Mod> b = km_sub(c1, c2, K, N);
  Mod res = Mod(0);
  REP(i,K) res += a[i] * b[i];
  return res;
}
