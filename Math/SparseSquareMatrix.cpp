SpMatrix scalar(int size, Data k) {
  REP(i,size) mat[i][i] = k;
  return mat;
}

SpMatrix operator^(const SpMatrix &lhs, const int n) {
  if (n == 0) return scalar(lhs.size(), 1);
  Matrix res = (lhs * lhs) ^ (n / 2);
  if (n % 2) res = res * lhs;
  return res;
}

Data det(SpMatrix A) {
  const int n = A.size();
  Data D = Data(1);
  for (int i = 0; i < n; ++i) {
    int pivot = i;
    while (!A.count(pivot) || !A[pivot].count(i)) ++pivot;
    for (int j = pivot+1; j < n; ++j)
      if (A.count(j) && A[j].count(i) && abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
    swap(A[pivot], A[i]);
    D = D * A[i][i] * Data(i != pivot ? -1 : 1);
    if (is_zero(A[i][i])) break;
    for(int j = i+1; j < n; ++j)
      if (A.count(j) && A[j].count(i))
        for(int k = n-1; k >= i; --k)
          A[j][k] = A[j][k] - A[i][k] * A[j][i] / A[i][i];
  }
  return D;
}

// LUP Decomposition
// PA = LU
//   |1 0 0|
// L=|* 1 0|
//   |* * 1|
//
//   |* * *|
// U=|0 * *|
//   |0 0 *|
//
//    |U U U|
//ret=|L U U| P:permutation
//    |L L U|,
pair<Matrix, vector<int>> LUPDecomposition(Matrix A) {
  int n=A.size();
  vector<int> perm(n);
  iota(begin(perm),end(perm),0);
  REP(i,n){
    int pivot = i;
    for(int j = i+1; j < n; ++j)
      if(abs(A[j][i]) > abs(A[pivot][i])) pivot = j;
    swap(A[pivot], A[i]);
    swap(perm[pivot], perm[i]);
    for(int j=i+1; j < n; ++j) {
      A[j][i] /= A[i][i];
      for (int k = i+1; k < n; ++k)
        A[j][k] -= A[i][k] * A[j][i];
    }
  }
  return make_pair(A, perm);
}

Array LUPBackSubstitution(Matrix& LU, vector<int>& perm, Array a) {
  int n=LU.size();
  REP(i,n) {
    swap(a[perm[i]], a[i]);
    REP(j,i) a[i] -= a[j] * LU[i][j];
  }
  for(int i=n-1; i >= 0; --i) {
    for(int j=i+1; j < n; ++j)
      a[i] -= a[j] * LU[i][j];
    a[i] /= LU[i][i];
  }
  return a;
}
