struct Data {
  int num;
  Data() : num(0) {;}
  Data(int n) : num(n) {;}
};

inline Data Merge(Data left, Data right) {
  return Data left.num + right.num;
}

struct Fenwick {
  static const int len = 1 << 18;
  Data data[len];
  Fenwick(void){ REP(i, len) data[i].num = 0; }
  void update(int i, Data value) {
    for (; i < len; i |= i+1) data[i] = Merge(dat[i], value);
  }
  Data query(int i) {
    Data s = 0;
    for (; i >= 0; i = (i&i+1)-1) s = Merge(s, data[i]);
    return s;
  }
};

// Light version

typedef int Data;
const int len = 1 << 18;

struct BIT {
  Data data[len];
  BIT(void){ REP(i, len) data[i] = 0;}
  void update(int i, Data value) {
    for (; i < len; i |= i+1) data[i] += value;
  }
  Data query(int i) {
    Data s = 0;
    for (; i >= 0; i = (i&i+1)-1) s += data[i];
    return s;
  }
};

// Range Add, Range Sum

struct RARS {
  BIT bit1, bit2;
  void add(int fr, int to, Data val) {
    bit1.update(fr, Data(-val.num * fr));
    bit1.update(to, Data(val.num * to));
    bit2.update(fr, val);
    bit2.update(to, Data(-val.num));
  }
  Data sum(int fr, int to) {
    Data s1 = bit1.query(to) + bit2.query(to) * to;
    Data s2 = bit1.query(fr) + bit2.query(fr) * fr;
    return Data(s1.num - s2.num);
  }
};
