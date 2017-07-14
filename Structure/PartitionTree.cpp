using Data = int;
struct PartitionTree {
  static const int size = 15;
  int n;
  Data ordered[1<<size];
  Data s[size+1][1<<size];
  int toLeft[size+1][1<<size];

  void build(int level, int l, int r) {
    if (r - l <= 1) return;
    int m = l + (r - l) / 2, cnt = m - l;
    Data mid = ordered[m];
    for (int i = l; i < r; ++i)
      if (s[level][i] < mid) --cnt;
    for (int i = l, j = l, k = m; i < r; ++i) {
      toLeft[level][i] = i == l ? 0 : toLeft[level][i - 1];
      if (s[level][i] < mid || (s[level][i] == mid && cnt > 0)) {
        s[level + 1][j++] = s[level][i];
        ++toLeft[level][i];
        if (s[level][i] == mid) --cnt;
      }
      else {
        s[level + 1][k++] = s[level][i];
      }
    }
    build(level + 1, l, m);
    build(level + 1, m, r);
  }

  PartitionTree(const vector<Data> &a) {
    n = a.size();
    REP(i,n) s[0][i] = a[i];
    REP(i,n) ordered[i] = a[i];
    sort(ordered, ordered + n);
    build(0, 0, n);
  }

  // query the k-th(1-based) smallest element in [lpos, rpos)
  Data query(int lpos, int rpos, int k) {
    int level = 0, l = 0, r = n;
    for (; r - l > 1; ++level) {
      int m = l + (r - l) / 2;
      int cntL = lpos == l ? 0 : toLeft[level][lpos - 1];
      int cntR = toLeft[level][rpos - 1];
      if (cntR - cntL >= k) {
        lpos = l + cntL;
        rpos = l + cntR;
        r = m;
      }
      else {
        lpos = m + lpos - l - cntL;
        rpos = m + rpos - l - cntR;
        k -= cntR - cntL;
        l = m;
      }
    }
    return s[level][l];
  }
};
