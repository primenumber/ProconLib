// verified : AOJ2090

const int INF = 1e9;

struct node {
  int value; node *next;
  node(int value, node *next) : value(value), next(next) { }
};

int index_of(vector<int> as, int x) {
  return lower_bound(as.begin(), as.end(), x) - as.begin();
}

vector<int> lcs(const vector<int> &a, const vector<int> &b) {
  const int n = a.size(), m = b.size();
  vector<vector<int>> M(256);
  for (int j = m-1; j >= 0; --j) M[b[j]].push_back(j);
  vector<int> xs(n+1, INF); xs[0] = -INF;
  vector<node*> link(n+1), del;
  REP(i,n) {
    if (M[a[i]].empty()) continue;
    vector<int> ys = M[a[i]];
    for (int j : ys) {
      int k = index_of(xs, j);
      xs[k] = j;
      link[k] = new node(b[j], link[k-1]);
      del.push_back(link[k]);
    }
  }
  int l = index_of(xs, INF-1) - 1;
  vector<int> c;
  for (node *p = link[l]; p; p = p->next)
    c.push_back(p->value);
  reverse(c.begin(), c.end());
  for (auto i : del) delete i;
  return c;
}
