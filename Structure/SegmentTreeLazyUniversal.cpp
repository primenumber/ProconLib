// Range Add - Range Min (Verified: SPOJ61)
struct Data {
  int num;
  Data() : num(0) {;}
  Data(int n) : num(n) {;}
};

const Data identity = Data(1000000000);

inline Data Merge(Data left, Data right) { return Data(min(left.num, right.num)); }
inline Data Set(Data lazy, Data val) { return Data(lazy.num + val.num); }
inline Data Eval(Data data, Data lazy, int num) { return Data(data.num + lazy.num); }

// Range Add - Range Sum (Unverified)
struct Data {
  int num;
  Data() : num(0) {;}
  Data(int n) : num(n) {;}
};

const Data identity = Data(0);

inline Data Merge(Data left, Data right) { return Data(left.num + right.num); }
inline Data Set(Data lazy, Data val) { return Data(lazy.num + val.num); }
inline Data Eval(Data data, Data lazy, int num) { return Data(data.num + lazy.num * num); }

// Range Set - Range Min (Unverified)
struct Data {
  int num;
  Data() : num(1000000000) {;}
  Data(int n) : num(n) {;}
};

const Data identity = Data(1000000000);

inline Data Merge(Data left, Data right) { return Data(min(left.num, right.num)); }
inline Data Set(Data lazy, Data val) { return val; }
inline Data Eval(Data data, Data lazy, int num) { return lazy; }

// Range Set - Range Sum (Unverified)
struct Data {
  int num;
  Data() : num(0) {;}
  Data(int n) : num(n) {;}
};

const Data identity = Data(0);

inline Data Merge(Data left, Data right) { return Data(left.num + right.num); }
inline Data Set(Data lazy, Data val) { return val; }
inline Data Eval(Data data, Data lazy, int num) { return Data(lazy.num * num); }

// Range Add, Set - Range Sum (Unverified)
struct Data {
  int type; // 0:data, 1:add, 2:set
  int num;
  Data() : type(0), num(0) {;}
  Data(int t, int n) : type(t), num(n) {;}
};

const Data identity = Data(0, 0);

inline Data Merge(Data left, Data right) { return Data(0, left.num + right.num); }
inline Data Set(Data lazy, Data val) {
  if (val.type == 2) return val;
  lazy.num += val.num; return lazy;
}
inline Data Eval(Data data, Data lazy, int num) {
  if (lazy.type == 2) return Data(0, lazy.num * num);
  return Data(0, data.num + lazy.num * num);
}

class SegmentTreeLazy {
  static const int MAX_DEPTH = 16;
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
