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
