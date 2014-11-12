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
