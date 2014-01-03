// 座標圧縮
typedef int Data;
vector<int> compressor(vector<Data> c) {
  int n = c.size();
  vector<Data> v(2 * n), w;
  vector<int> res(n);
  REP(i,n) v[2*i] = c[i], v[2*i+1] = c[i] + 1;
  sort(v.begin(), v.end());
  REP(i,v.size()) if (i == 0 || v[i] != v[i-1]) w.push_back(v[i]);
  REP(i,n) res[i] = lower_bound(w.begin(), w.end(), c[i]) - w.begin();
  return res;
}
