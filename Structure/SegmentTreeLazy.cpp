struct SegTreeLazy {
  static const int MAX_DEPTH = 18;
  static const int STsize = 1 << MAX_DEPTH;
  Data data[STsize];
  Data lazy[STsize]; int n;
  SegTreeLazy(void) : n(STsize / 2) {
    REP(i,STsize){
      data[i]=lazy[i]=0;
    }
  }
  void add(int fr, int to, Data val) { upd_sub(fr, to, 2*n-2, 0, n, val); }
  Data sum(int fr, int to) { return sum_sub(fr, to, 2*n-2, 0, n); }
 private:
  void upd_sub(int fr, int to, int node, int la, int ra, Data val) {
    if (ra<=fr || to<=la) return;
    if (fr<=la && ra<=to) {
      lazy[node] += val; return;
    }
    data[node] += (min(to, ra) - max(fr, la)) * val;
    upd_sub(fr, to, (node-n)*2+0, la, (la+ra)/2, val);
    upd_sub(fr, to, (node-n)*2+1, (la+ra)/2, ra, val);
  }
  Data sum_sub(int fr, int to, int node, int la, int ra) {
    if (ra<=fr || to<=la) return Data();
    if (fr<=la && ra<=to) return data[node] + lazy[node]*(ra-la);
    Data res = lazy[node] * (min(to, ra) - max(fr, la));
    res += sum_sub(fr, to, (node-n)*2+0, la, (la+ra)/2);
    res += sum_sub(fr, to, (node-n)*2+1, (la+ra)/2, ra);
    return res;
  }
};
