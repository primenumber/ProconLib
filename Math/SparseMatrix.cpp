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
map<int, T> merge(map<int, T> lhs, const map<int, T>& rhs, Func& func = Func()) {
  for(auto& rp:rhs) {
    if (lhs.count(rp.first))
      lhs[rp.first] = func(lhs[rp.first], rp.second);
    else
      lhs.insert(rp);
  }
  return lhs;
}

template<typename Func>
SpMatrix binary_op(const SpMatrix& lhs, const SpMatrix& rhs) {
  return merge(lhs, rhs, merge<Data, Func>);
}

SpMatrix operator+(const SpMatrix& lhs, const SpMatrix &rhs) {
  return binary_op<plus<Data>>(lhs, rhs);
}

Matrix operator-(Matrix lhs, const Matrix &rhs) {
  return binary_op<minus<Data>>(lhs, rhs);
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
  Matrix res(lhs.size(), Array(rhs[0].size(), 0));
  REP(i,lhs.size()) REP(j,rhs[0].size()) REP(k,rhs.size())
    res[i][j] = res[i][j] + lhs[i][k] * rhs[k][j];
  return res;
}

int rankMat(Matrix A) {
  const int n = A.size(), m = A[0].size();
  int r = 0;
  for (int i = 0; r < n && i < m; ++i) {
    int pivot = r;
    for (int j = r+1; j < n; ++j)
      if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
    swap(A[pivot], A[r]);
    if (is_zero(A[r][i])) continue;
    for (int k = m-1; k >= i; --k)
      A[r][k] = A[r][k] / A[r][i];
    for(int j = r+1; j < n; ++j)
      for(int k = m-1; k >= i; --k)
        A[j][k] = A[j][k] - (A[r][k] * A[j][i]);
    ++r;
  }
  return r;
}
