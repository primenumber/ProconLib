using Data = int;
const Data INF = 1000000000;

vector<Data> lis(const vector<Data>& a) {
  const int n = a.size();
  if (n == 0) return vector<Data>(0);
  vector<Data> A(n, INF);
  vector<int> id(n);
  for (int i = 0; i < n; i++) {
    id[i] = distance(A.begin(), lower_bound(A.begin(), A.end(), a[i]));
    A[id[i]] = a[i];
  }
  int m = *max_element(id.begin(), id.end());
  vector<Data> res(m + 1);
  for (int i = n - 1; i >= 0; i--)
    if (id[i] == m) res[m--] = a[i];
  return res;
}
