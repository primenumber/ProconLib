
// Fenwick Tree

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

// Light Fenwick Tree

typedef int Data;
const int len = 1 << 18;

class BIT {
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
