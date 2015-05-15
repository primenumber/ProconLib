// Big Range Query
// (verified : KOJ0042)

// initialize : [0, 1, 2, ...]
// update(t, p, v) : set value v in t[p]
// query(t, x, y) : min[x, y) and max[x, y) of t

struct Data {
  int mi, ma;
  Data() : mi(0x7FFFFFFF), ma(0x80000000) {;}
  Data(int n) : mi(n), ma(n) {;}
  Data(int n, int m) : mi(n), ma(m) {;}
};

inline Data Merge(Data left, Data right) {
  return Data(min(left.mi, right.mi), max(left.ma, right.ma));
}

inline Data init(int left, int right) { return Data(left, right - 1); }

struct BigRMQ {
  int lpos, rpos;
  Data value;
  BigRMQ *left, *right;
  BigRMQ()
    : lpos(0), rpos(1<<30), value(Data()),
      left(nullptr), right(nullptr) {}
  BigRMQ(int l, int r)
    : lpos(l), rpos(r), value(init(l, r)),
      left(nullptr), right(nullptr) {}
};

Data val(BigRMQ *t, int l, int r) {
  if (!t) return init(l, r); else return t->value;
}

void update(BigRMQ *t, int pos, Data value) {
  if (t->rpos - t->lpos <= 1) { t->value = value; return; }
  int lpos = t->lpos, rpos = t->rpos;
  int mid = (t->lpos + t->rpos) / 2;
  if (pos < mid) {
    if (!(t->left)) t->left = new BigRMQ(lpos, mid);
    update(t->left, pos, value);
  }
  else {
    if (!(t->right)) t->right = new BigRMQ(mid, rpos);
    update(t->right, pos, value);
  }
  t->value = Merge(val(t->left, lpos, mid), val(t->right, mid, rpos));
}

Data query(BigRMQ *t, int fr, int to) {
  if (fr >= to) return Data();
  if (!t) return init(fr, to);
  if (t->rpos <= fr || to <= t->lpos) return Data();
  if (fr <= t->lpos && t->rpos <= to) return t->value;
  int mid = (t->lpos + t->rpos) / 2;
  Data vl = query(t->left, fr, min(to, mid));
  Data vr = query(t->right, max(fr, mid), to);
  return Merge(vl, vr);
}

// main

int main() {
  int N, Q;
  cin >> N >> Q;
  BigRMQ seg(0, N+1);
  REP(i,Q) {
    int a, b, c;
    cin >> a >> b >> c;
    if (a == 1) cout << query(&seg, b, c+1).mi << endl;
    if (a == 2) cout << query(&seg, b, c+1).ma << endl;
    if (a == 3) update(&seg, b, Data(c));
  }
  return 0;
}
