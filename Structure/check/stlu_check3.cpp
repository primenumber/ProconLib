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
