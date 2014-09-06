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
