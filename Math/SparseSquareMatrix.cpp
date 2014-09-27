SpMatrix scalar(int size, Data k) {
  REP(i,size) mat[i][i] = k;
  return mat;
}

Array CG_method_impl(const SpMatrix& A, const SpMatrix& A_t, const Array& b) {
  Array r_old = b;
  Array p_old = r_old;
  Array x(b.size(), Data(0));
  REP(i,b.size()) {
    Data alpha = norm(r_old) / norm(A * p_old); // p^T * A^T * A * p = (A*p)^T * (A*p) = norm(A*p)
    x = x + alpha * p_old;
    Array r_new = r_old - alpha * (A_T * (A * p_old));
    if (is_zero(r_new)) break;
    Data beta = norm(r_new) / norm(r_old);
    p_new = r_new + beta * p_old;
    r_new.swap(r_old);
    p_new.swap(p_old);
  }
  return x;
}

// solve System of linear equations
Array CG_method(const SpMatrix& A, const SpArray& b, int n) {
  SpMatrix A_t = transpose(A);
  Array b_prime = mult(ary, spmat, 1, n)[0]; //A^T * b^T = (b * A)^T
  return CG_method_impl(A, A_t, b_prime); // A^T * A * x^T = A^T * b^T
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
          if (A[i].count(k))
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
