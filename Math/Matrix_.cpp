typedef long double Data;
typedef vector<Data> Array;
typedef vector<Array> Matrix;

bool is_zero(Data dat) { return (abs(dat) < eps); }

Matrix scalar(int size, Data k) {
  Matrix mat(size, Array(size, 0));
  REP(i,size) mat[i][i] = k;
  return mat;
}

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
    res[i][j] = res[i][j] + lhs[i][k] * rhs[k][j];
  return res;
}

Matrix operator^(const Matrix &lhs, const int n) {
  if (n == 0) return scalar(lhs.size(), 1);
  Matrix res = (lhs * lhs) ^ (n / 2);
  if (n % 2) res = res * lhs;
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
