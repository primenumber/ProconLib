struct RBST {
  Data value;
  RBST *left;
  RBST *right;
  int cnt;
  Data sum;
  RBST(Data v)
    : value(v), left(nullptr), right(nullptr),
    cnt(1), sum(v) {}
};

int count(RBST *t) { return !t ? 0 : t->cnt; }
Data sum(RBST *t) { return !t ? 0 : t->sum; }
RBST *update(RBST *t) {
  t->cnt = count(t->left) + count(t->right) + 1;
  t->sum = sum(t->left) + sum(t->right) + t->value;
  return t;
}

RBST *merge(RBST *l, RBST *r) {
  if (!l || !r) return !l ? r : l;

  int cnt_sum = count(l) + count(r);
  // rand()だと小さい値しか返さない実装になっていることがあるので、適当な実装を使う
  if ((my_rand() % cnt_sum) < count(l)) {
    l->right = merge(l->right, r);
    return update(l);
  } else {
    r->left = merge(l, r->left);
    return update(r);
  }
}

pair<RBST*, RBST*> split(RBST *t, int k) {
  if (!t) return make_pair(nullptr, nullptr);
  
  if (k <= count(t->left)) {
    auto s = split(t->left, k);
    t->left = s.second;
    return make_pair(s.first, update(t));
  } else {
    auto s = split(t->right, k - count(t->left) - 1);
    t->right = s.first;
    return make_pair(update(t), s.second);
  }
}

RBST *insert(RBST *t, int k, Data v) {
  auto s = split(t, k);
  return merge(s.first, merge(new RBST(v), s.second));
}

RBST *erase(RBST *t, int k) {
  auto s1 = split(t, k);
  auto s2 = split(s1.second, 1);
  delete s2.first;
  return merge(s1.first, s2.second);
}
