#include <bits/stdc++.h>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
#include "stlu_check1.cpp"

class SegmentTreeLazy {
  static const int MAX_DEPTH = 17;
  static const int STsize = 1 << MAX_DEPTH;
  Data data[STsize], lazy[STsize];
  bool flag[STsize]; int n;
  void lazyset(int node, Data val) {
    if (flag[node]) lazy[node] = Set(lazy[node], val);
    else lazy[node] = val;
    flag[node] = true;
  }
  void evaluate(int node, int num) {
    if (!flag[node]) return;
    Data val = lazy[node];
    data[node] = Eval(data[node], val, num); flag[node] = false;
    if (node < n) return;
    lazyset((node-n)*2+0, val); lazyset((node-n)*2+1, val);
  }
  void update_sub(int fr, int to, int node, int la, int ra, Data val) {
    if (ra <= fr || to <= la) { evaluate(node, ra - la); return; }
    if (fr <= la && ra <= to) {
      lazyset(node, val); evaluate(node, ra - la); return;
    }
    evaluate(node, ra - la);
    int lpos = (node-n)*2+0, rpos = (node-n)*2+1;
    update_sub(fr, to, lpos, la, (la+ra)/2, val);
    update_sub(fr, to, rpos, (la+ra)/2, ra, val);
    data[node] = Merge(data[lpos], data[rpos]);
  }
  Data query_sub(int fr, int to, int node, int la, int ra) {
    if (ra<=fr || to<=la) return identity;
    if (fr<=la && ra<=to) { evaluate(node, ra - la); return data[node]; }
    evaluate(node, ra - la);
    Data l = query_sub(fr, to, (node-n)*2+0, la, (la+ra)/2);
    Data r = query_sub(fr, to, (node-n)*2+1, (la+ra)/2, ra);
    return Merge(l, r);
  }
public:
  SegmentTreeLazy(void) : n(STsize / 2) { REP(i,STsize) flag[i] = false; }
  void update(int fr, int to, Data val) { update_sub(fr, to, 2*n-2, 0, n, val); }
  Data query(int fr, int to) { return query_sub(fr, to, 2*n-2, 0, n); }
};

class Naive {
  static const int N = 1024;
  Data data[N];
 public:
  void update(int fr, int to, Data val) {
    for (int i = fr; i < to; ++i)
      data[i] = Set(data[i], val);
  }
  Data query(int fr, int to) {
    Data res = identity;
    for (int i = fr; i < to; ++i)
      res = Merge(res, data[i]);
    return res;
  }
};

/* (range set, add range sum)
int main() {
  Naive naive;
  SegmentTreeLazy seg;
  int n,m,l;
  cin>>n>>m>>l;
  cout << "Phase 1: N <= 1024, Compare with naive structure" << endl;
  REP(i,n) {
    int c = rand() % 3;
    int fr = rand() % 1024;
    int to = rand() % (1024 - fr) + fr;
    if (c != 0) {
      int v;
      v = rand() % 1000 - 500;
      naive.update(fr, to, Data(c, v));
      seg.update(fr, to, Data(c, v));
    } else {
      Data n = naive.query(fr, to);
      Data s = seg.query(fr, to);
      if (n.num != s.num) {
        cout << "bug" << endl;
        cout << fr << ' ' << to << endl;
        cout << i << endl;
        cout << n.num << ' ' << s.num << endl;
      }
    }
  }
  cout << "Phase 2: N <= 60000, Check time" << endl;
  SegmentTreeLazy seg2;
  REP(i,m) {
    int c = rand() % 3;
    int fr = rand() % 60000;
    int to = rand() % (60000- fr) + fr;
    Data s;
    if (c != 0) {
      int v;
      v = rand() % 1000 - 500;
      seg2.update(fr, to, Data(c, v));
    } else {
      s = Merge(s, seg2.query(fr, to));
    }
  }
  cout << "Phase 3: N <= 10, Check corner cases" << endl;
  SegmentTreeLazy seg3;
  Naive naive3;
  REP(i,l) {
    int c = rand() % 3;
    int fr = rand() % 1024;
    int to = rand() % (1024 - fr) + fr;
    if (c != 0) {
      int v;
      v = rand() % 1000 - 500;
      naive3.update(fr, to, Data(c, v));
      seg3.update(fr, to, Data(c, v));
    } else {
      Data n = naive3.query(fr, to);
      Data s = seg3.query(fr, to);
      if (n.num != s.num) {
        cout << "bug" << endl;
        cout << fr << ' ' << to << endl;
        cout << i << endl;
        cout << n.num << ' ' << s.num << endl;
      }
    }
  }
  return 0;
}
*/

int main() {
  Naive naive;
  SegmentTreeLazy seg;
  int n,m,l;
  cin>>n>>m>>l;
  cout << "Phase 1: N <= 1024, Compare with naive structure" << endl;
  REP(i,n) {
    int c = rand() % 2;
    int fr = rand() % 1024;
    int to = rand() % (1024 - fr) + fr;
    if (c != 0) {
      int v;
      v = rand() % 1000 - 500;
      naive.update(fr, to, Data(v));
      seg.update(fr, to, Data(v));
    } else {
      Data n = naive.query(fr, to);
      Data s = seg.query(fr, to);
      if (n.num != s.num) {
        cout << "bug" << endl;
        cout << fr << ' ' << to << endl;
        cout << i << endl;
        cout << n.num << ' ' << s.num << endl;
      }
    }
  }
  cout << "Phase 2: N <= 60000, Check time" << endl;
  SegmentTreeLazy seg2;
  REP(i,m) {
    int c = rand() % 2;
    int fr = rand() % 60000;
    int to = rand() % (60000- fr) + fr;
    Data s;
    if (c != 0) {
      int v;
      v = rand() % 1000 - 500;
      seg2.update(fr, to, Data(v));
    } else {
      s = Merge(s, seg2.query(fr, to));
    }
  }
  cout << "Phase 3: N <= 10, Check corner cases" << endl;
  SegmentTreeLazy seg3;
  Naive naive3;
  REP(i,l) {
    int c = rand() % 2;
    int fr = rand() % 1024;
    int to = rand() % (1024 - fr) + fr;
    if (c != 0) {
      int v;
      v = rand() % 1000 - 500;
      naive3.update(fr, to, Data(v));
      seg3.update(fr, to, Data(v));
    } else {
      Data n = naive3.query(fr, to);
      Data s = seg3.query(fr, to);
      if (n.num != s.num) {
        cout << "bug" << endl;
        cout << fr << ' ' << to << endl;
        cout << i << endl;
        cout << n.num << ' ' << s.num << endl;
      }
    }
  }
  return 0;
}
