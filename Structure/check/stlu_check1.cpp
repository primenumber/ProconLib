#include <bits/stdc++.h>

using namespace std;

#define REP(i,n) for(int i = 0; i < (int)(n); ++i)
// Range Add - Range Min (Verified: SPOJ61)
struct Data {
  int64_t num;
  Data() : num(0) {;}
  Data(int n) : num(n) {;}
};

const Data identity = Data(1000000000);

inline Data Merge(Data left, Data right) { return Data(min(left.num, right.num)); }
inline Data Set(Data lazy, Data val) { return Data(lazy.num + val.num); }
inline Data Eval(Data data, Data lazy, int num) { return Data(data.num + lazy.num); }

