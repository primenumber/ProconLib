typedef int Data;
int N, K;
int a[1024];

int LowerBound(Data k) {
  int lb = -1, ub = N;
  while (ub - lb > 1) {
    int mid = (lb + ub) / 2;
    if (a[mid] >= K) ub = mid; else lb = mid;
  }
  return ub;
}
