// Verified AOJ (TLE)

struct PA {
  int p, rank;
  PA *l, *r;
  PA(int p, PA *l, PA *r) : p(p), rank(0), l(l), r(r) {}
  PA(int p, int rank, PA *l, PA *r) : p(p), rank(rank), l(l), r(r) {};
};

PA *create(int n, int a = 1, int b = 0) {
  if (n == 0) { return nullptr; }
  int ln = n >> 1, rn = n - ln - 1;
  PA *res = new PA(b, create(ln, a * 2, a + b), create(rn, a * 2, a * 2 + b));
  return res;
}

PA *get_(PA *uf, int n) {
  if (n == 0) return uf;
  return get_((n & 1) ? uf->l : uf->r, (n - 1) >> 1);
}

PA *set_(PA *uf, int n, int x, int rank) {
  if (n == 0) return new PA(x, rank, uf->l, uf->r);
  if (n & 1) {
    PA *p = set_(uf->l, (n - 1) >> 1, x, rank);
    return new PA(uf->p, uf->rank, p, uf->r);
  }
  else {
    PA *p = set_(uf->r, (n - 1) >> 1, x, rank);
    return new PA(uf->p, uf->rank, uf->l, p);
  }
}

PA *root(PA *uf, int x) {
  PA *p = get_(uf, x);
  return p->p == x ? p : root(uf, p->p);
}

PA *merge(PA *uf, int x, int y) {
  PA *l = root(uf, x), *r = root(uf, y);
  if (l->p == r->p) return uf;
  if (l->rank < r->rank) swap(l, r);
  int rank = l->rank + (l->rank == r->rank);
  PA *res = set_(uf, r->p, l->p, rank);
  res = set_(res, l->p, l->p, rank);
  return res;
}

// int main() {
//   int n, q;
//   cin >> n >> q;
//   PA *uf = create(n);
//   while (q--) {
//     int a, b, c;
//     cin >> a >> b >> c;
//     if (a) {
//       cout << (root(uf, b) == root(uf, c)) << endl;
//     }
//     else {
//       uf = merge(uf, b, c);
//     }
//   }
//   return 0;
// }
