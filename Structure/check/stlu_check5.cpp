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
