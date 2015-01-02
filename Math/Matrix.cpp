typedef long double Data;
typedef vector<Data> Array;
typedef vector<Array> Matrix;

bool is_zero(Data dat) { return (abs(dat) < eps); }

Matrix operator-(Matrix mat) {
  REP(i,mat.size()) REP(j,mat[0].size()) mat[i][j] = -mat[i][j];
  return mat;
}

Matrix operator+(Matrix lhs, const Matrix &rhs) {
  REP(i,lhs.size()) REP(j,lhs[0].size()) lhs[i][j] = lhs[i][j] + rhs[i][j];
  return lhs;
}

Matrix operator-(Matrix lhs, const Matrix &rhs) {
  REP(i,lhs.size()) REP(j,lhs[0].size()) lhs[i][j] = lhs[i][j] - rhs[i][j];
  return lhs;
}

Matrix operator*(const Matrix &lhs, const Matrix &rhs) {
  Matrix res(lhs.size(), Array(rhs[0].size(), 0));
  REP(i,lhs.size()) REP(j,rhs[0].size()) REP(k,rhs.size())
    res[i][j] = fma(lhs[i][k], rhs[k][j], res[i][j]);
  return res;
}

Array operator+(const Array &lhs, const Array &rhs) {
  Array res = lhs;
  REP(i,rhs.size()) res[i] = res[i] + rhs[i];
  return res;
}

Array operator*(const Matrix &lhs, const Array &rhs) {
  Array res(lhs.size());
  REP(i,lhs.size())
    res[i] = inner_product(begin(lhs[i]),end(lhs[i]),begin(rhs),Data(0));
  return res;
}

Array operator*(Data scalar, const Array &rhs) {
  Array res(rhs.size());
  REP(i,rhs.size())
    res[i] = scalar * rhs[i];
  return res;
}

Matrix transpose(const Matrix &A) {
  const int n = A[0].size(), m = A.size();
  Matrix res(n, Array(m, 0));
  REP(i,n)REP(j,m) res[i][j] = A[j][i];
  return res;
}

Data inner_product_ex(const Array& a, const Array& b, const Matrix& m) {
  Array b_prime = m*b;
  return inner_product(begin(a),end(a),begin(b_prime),Data(0));
}

Data norm(const Array &a) {
  return inner_product(begin(a),end(a),begin(a),Data(0));
}

Data norm(const Array &a, const Matrix &M) {
  return inner_product_ex(a,a,M);
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
        A[j][k] = fma(-A[r][k], A[j][i], A[j][k]);
    ++r;
  }
  return r;
}

Data det(Matrix A) {
  const int n = A.size();
  Data D = Data(1);
  for (int i = 0; i < n; ++i) {
    int pivot = i;
    for (int j = i+1; j < n; ++j)
      if (abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
    swap(A[pivot], A[i]);
    D = D * A[i][i] * Data(i != pivot ? -1 : 1);
    if (is_zero(A[i][i])) break;
    for(int j = i+1; j < n; ++j)
      for(int k = n-1; k >= i; --k)
        A[j][k] = A[j][k] - A[i][k] * A[j][i] / A[i][i];
  }
  return D;
}
