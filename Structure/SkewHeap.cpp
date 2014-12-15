// no reduce
struct Heap {
  shared_ptr<Heap> l,r;
  Data val;
  Heap(Data v) : val(v) {}
  Data top() { return val; }
};
shared_ptr<Heap> meld(shared_ptr<Heap> a, shared_ptr<Heap> b) {
  if (!a) return b;
  if (!b) return a;
  if (a->val > b->val) swap(a, b);
  a->r = meld(a->r, b);
  swap(a->l, a->r);
  return a;
}
shared_ptr<Heap> push(shared_ptr<Heap> h, Data v) {
  return meld(h, make_shared<Heap>(v));
}
shared_ptr<Heap> pop(shared_ptr<Heap> h) {
  return meld(h->l, h->r);
}

// enable reduce
struct Heap {
  shared_ptr<Heap> l,r,p;
  Data val;
  Heap(Data v) : val(v) {}
  Data top() { return val; }
};
int cnt1, cnt2;
shared_ptr<Heap> meld(
    shared_ptr<Heap> a, shared_ptr<Heap> b, shared_ptr<Heap> p = nullptr) {
  ++cnt1;
  if(p==nullptr) ++cnt2;
  if (!a) {
    if (b) b->p = p;
    return b;
  }
  if (!b) {
    if (a) a->p = p;
    return a;
  }
  if (a->val > b->val) swap(a, b);
  a->p = p;
  a->r = meld(a->r, b, a);
  swap(a->l, a->r);
  return a;
}
pair<shared_ptr<Heap>, shared_ptr<Heap>> push(shared_ptr<Heap> h, Data v) {
  auto n = make_shared<Heap>(v);
  return make_pair(meld(h, n), n);
}
shared_ptr<Heap> pop(shared_ptr<Heap> h) {
  if (h->l) h->l->p.reset();
  if (h->r) h->r->p.reset();
  return meld(h->l, h->r);
}
shared_ptr<Heap> reduce(shared_ptr<Heap> h, shared_ptr<Heap> root, Data v) {
  if (v > h->val) return root;
  h->val = v;
  if (!h->p) return root;
  if (h->val < h->p->val) {
    if (h->p->l && h->p->l == h) {
      h->p->l.reset();
      return meld(h, root);
    } else {
      h->p->r.reset();
      return meld(h, root);
    }
  } else return root;
}
