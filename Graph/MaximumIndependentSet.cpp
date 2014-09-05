#define MAX_V 100

//O(n*1.4656^n)
vector<int> MaximumIndependentSet(vector<bitset<MAX_V>>& g, bitset<MAX_V> usable) {
  int n=g.size();
  int v=-1;
  vector<int> res;
  REP(i,n) {
    if(!usable[i]) continue;
    int neigh = (usable & g[i]).count();
    if (neigh <= 1) {
      usable[i] = false;
      usable &= ~g[i];
      res.push_back(i);
    } else {
      v = i;
    }
  }
  if (v < 0) return res;
  usable[v] = false;
  bitset<MAX_V> used = usable & ~g[v];
  auto res1 = MaximumIndependentSet(g, used);
  res1.push_back(v);
  auto res2 = MaximumIndependentSet(g, usable);
  if (res1.size() > res2.size())
    res.insert(end(res),begin(res1),end(res1));
  else
    res.insert(end(res),begin(res2),end(res2));
  return res;
}
