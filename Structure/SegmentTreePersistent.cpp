// Persistent Segment Tree
// Range add Range sum
// Verified : AOJ2563

using Data = ll;

struct PST {
  Data val, lazy;
  PST *l, *r;
  PST() : val(0), lazy(0), l(nullptr), r(nullptr) {}
  PST(Data val, Data lazy, PST *l, PST *r) : val(val), lazy(lazy), l(l), r(r) {}
};

Data value(PST* ptr) { if (ptr) return ptr->val; else return 0; }
Data lazy(PST* ptr) { if (ptr) return ptr->lazy; else return 0; }
PST *left(PST* ptr) { if (ptr) return ptr->l; else return nullptr; }
PST *right(PST* ptr) { if (ptr) return ptr->r; else return nullptr; }

PST *add(PST *ptr, int lpos, int rpos, Data val, int la, int ra) {
  if (rpos <= la || ra <= lpos) return ptr;
  if (lpos <= la && ra <= rpos) {
    return new PST(value(ptr), lazy(ptr) + val, left(ptr), right(ptr));
  }
  int mid = (la + ra) / 2;
  PST *l = add(left(ptr),  lpos, rpos, val, la, mid);
  PST *r = add(right(ptr), lpos, rpos, val, mid, ra);
  int c = min(ra, rpos) - max(la, lpos);
  return new PST(value(ptr) + c * val, lazy(ptr), l, r);
}

Data sum(PST *ptr, int lpos, int rpos, int la, int ra) {
  if (!ptr || rpos <= la || ra <= lpos) return Data(0);
  if (lpos <= la && ra <= rpos) return ptr->val + ptr->lazy * (ra - la);
  int mid = (la + ra) / 2;
  Data res = ptr->lazy * (min(rpos, ra) - max(lpos, la));
  res += sum(ptr->l, lpos, rpos, la, mid);
  res += sum(ptr->r, lpos, rpos, mid, ra);
  return res;
}
