
// Treap

struct Treap {
  Data value;
  int pri;
  Treap *left;
  Treap *right;
  int cnt;
  int sum;
  Treap(Data v)
      : value(v), pri(rand()),
      left(nullptr), right(nullptr),
      cnt(1), sum(v) {}
};

int count(Treap *t) { return !t ? 0 : t->cnt; }
int sum(Treap *t) { return !t ? 0 : t->sum; }

Treap *update(Treap *t) {
  t->cnt = count(t->left) + count(t->right) + 1;
  t->sum = sum(t->left) + sum(t->right) + t->value;
  return t;
}

Treap *merge(Treap *l, Treap *r){
  if(!l || !r) return !l ? r : l;

  if(l->pri > r->pri){
    l->right = merge(l->right, r);
    return update(l);
  } else {
    r->left = merge(l, r->left);
    return update(r);
  }
}

pair<Treap*, Treap*> split(Treap *t, int k) {
  if(!t) return make_pair(nullptr, nullptr);

  if(k <= count(t->left)) {
    auto s = split(t->left, k);
    t->left = s.second;
    return make_pair(s.first, update(t));
  } else {
    auto s = split(t->right, k - count(t->left) - 1);
    t->right = s.first;
    return make_pair(update(t), s.second);
  }
}

Treap *insert(Treap *t, int k, Data v) {
  auto s = split(t, k);
  return merge(s.first, merge(new Treap(v), s.second));
}

Treap *erase(Treap *t, int k) {
  auto s1 = split(t, k);
  auto s2 = split(s1.second, 1);
  free(s2.first);
  return merge(s1.first, s2.second);
}
