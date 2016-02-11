struct SuffixArray {
  struct SAComp {
    const int h;
    const vector<int> &g;
    SAComp(int h, vector<int> &g) : h(h), g(g) {;}
    bool operator() (int a, int b) {
      return a != b && (g[a] != g[b] ? g[a] < g[b] : g[a + h] < g[b + h]);
    }
  };

  int n;
  char *str;
  vector<int> sa, lcp;

  SuffixArray(const string &t) : n(t.size()), sa(n+1), lcp(n+1) {
    str = new char[n+1];
    strcpy(str, t.c_str());

    // build SA
    vector<int> g(n+1, 0), b(n+1, 0);
    REP(i,n+1) { sa[i] = i; g[i] = str[i]; }
    sort(begin(sa), end(sa), SAComp(0, g));
    for (int h = 1; b[n] != n; h *= 2) {
      SAComp comp(h, g);
      sort(sa.begin(), sa.end(), comp);
      REP(i,n) b[i+1] = b[i] + comp(sa[i], sa[i+1]);
      REP(i,n+1) g[sa[i]] = b[i];
    }

    // build LCP
    int h = 0;
    REP(i,n+1) b[sa[i]] = i;
    REP(i,n+1) {
      if (b[i]) {
        for (int j = sa[b[i]-1]; j+h<n && i+h<n && str[j+h] == str[i+h]; ++h);
        lcp[b[i]] = h;
      }
      else {
        lcp[b[i]] = -1;
      }
      if (h > 0) --h;
    }
  }
  ~SuffixArray() { delete []str; }

  int find(string t) {
    int m = t.size();
    char p[m+1];
    strcpy(p, t.c_str());
    int left = -1, right = n + 1;
    while (left + 1 < right) {
      int mid = (left + right) / 2;
      if (strncmp(str + sa[mid], p, m) < 0) left = mid;
      else right = mid;
    }
    return strncmp(str + sa[right], p, m) == 0 ? sa[right] : -1;
  }
};
