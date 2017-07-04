SpMat scalar(int size, Data k) {
  SpMat res;
  REP(i,size) res.emplace_back(make_pair(i, i), k);
  return res;
}

// Solve A^t * A * x = b
Array CG_method_impl(const SpMat& A, const SpMat& A_t, const Array& b) {
  Array r_old = b;
  Array p_old = r_old;
  Array x(b.size(), Data(0));
  while(true) {
    Array Axp = mult(A, p_old, p_old.size());
    Data alpha = norm(r_old) / norm(Axp); // p^T * A^T * A * p = (A*p)^T * (A*p) = norm(A*p)
    x = x + alpha * p_old;
    Array r_new = r_old  + -alpha * mult(A_t, mult(A, p_old, p_old.size()), p_old.size());
    if (all_of(begin(r_new),end(r_new),is_zero)) break;
    Data beta = norm(r_new) / norm(r_old);
    Array p_new = r_new + beta * p_old;
    r_new.swap(r_old);
    p_new.swap(p_old);
  }
  return x;
}

// Solve System of linear equations
// Solve least square problem when A is not full rank
Array CG_method(const SpMat& A, const Array& b, int n) {
  SpMat A_t = transpose(A);
  Array b_prime = mult(b, A, n); //A^T * b^T = (b * A)^T
  return CG_method_impl(A, A_t, b_prime); // A^T * A * x^T = A^T * b^T
}
