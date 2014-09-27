typedef long double Data;
typedef vector<Data> Array;
typedef map<int, Data> SpArray;
typedef map<int, SpArray> SpMatrix;

bool is_zero(Data dat) { return (abs(dat) < eps); }

SpMatrix operator-(SpMatrix mat) {
  for(auto& v:mat)
    for(auto& p:v.second)
      p.second = -p.second;
  return mat;
}

template<typename T, typename Func>
map<int, T> merge(map<int, T> lhs, const map<int, T>& rhs, Func func) {
  for(auto& rp:rhs) {
    if (lhs.count(rp.first))
      lhs[rp.first] = func(lhs[rp.first], rp.second);
    else
      lhs.insert(rp);
  }
  return lhs;
}

template<typename Func>
SpMatrix binary_op(const SpMatrix& lhs, const SpMatrix& rhs, Func func) {
  return merge(lhs, rhs,
      bind(merge<Data, Func>, placeholders::_1, placeholders::_2, func));
}

SpMatrix operator+(const SpMatrix& lhs, const SpMatrix &rhs) {
  return binary_op(lhs, rhs, plus<Data>());
}

SpMatrix operator-(const SpMatrix& lhs, const SpMatrix &rhs) {
  return binary_op(lhs, rhs, minus<Data>());
}

Matrix to_mat(const SpMatrix &spmat, int row, int col) {
  Matrix res(row, Array(col, 0));
  for (auto& l:spmat) {
    for (auto& v:l.second){
      int i=l.first;
      int j=v.first;
      res[i][j] = v.second;
    }
  }
  return res;
}

Matrix mult(const SpMatrix &lhs, const SpMatrix &rhs, int row, int col) {
  Matrix res(row, Array(col, 0));
  for (auto& l:lhs) {
    for (auto& v:l.second){
      int i=l.first;
      int k=v.first;
      if (!rhs.count(k)) continue;
      for (auto& r:rhs.find(k)->second){
        int j=r.first;
        res[i][j] = res[i][j] + v.second * r.second;
      }
    }
  }
  return res;
}

Array mult(const SpMatrix &lhs, const Array &rhs, int len) {
  Array res(len, 0);
  for (auto& l:lhs) {
    int i = l.first;
    for (auto& v:l.second)
      res[i] = res[i] + v.second * rhs[v.first];
  }
  return res;
}

//rankmat for SparseMatrix is none
