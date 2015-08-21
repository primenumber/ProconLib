typedef int Data;
vector<int> compressor(vector<Data> c) {
  const int n = c.size();
  vector<Data> v = c;
  vector<int> res(n);
  sort(v.begin(), v.end());
  auto it = unique(ALL(v));
  REP(i,n) res[i] = lower_bound(begin(v), it, c[i]) - begin(v);
  return res;
}
