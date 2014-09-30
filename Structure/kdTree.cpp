// Point:valarray<T>
ld dist_pc(const Point &p_, const Point &top, const Point &btm) {
  ld dist = 0.0;
  REP(i,3) {
    if (top[i] < p_[i]) dist += (p_[i] - top[i]) * (p_[i] - top[i]);
    if (p_[i] < btm[i]) dist += (p_[i] - btm[i]) * (p_[i] - btm[i]);
  }
  return sqrt(dist);
}

#define DIM 3
struct kdTree {
  Point p;
  kdTree *l, *r;
  kdTree(const Point &p_) : p(p_), l(nullptr), r(nullptr) {}
  kdTree *insert(const Point &p_, int dep = 0) {
    if (p[dep] > p_[dep]) {
      if (l == nullptr) return l = new kdTree(p_);
      else return l->insert(p_, (dep+1)%DIM);
    } else {
      if (r == nullptr) return r = new kdTree(p_);
      else return r->insert(p_, (dep+1)%DIM);
    }
  }
  kdTree *nearer(const Point &p_, kdTree *x, kdTree *y) {
    ld dx = dist(p_ - x->p);
    ld dy = dist(p_ - y->p);
    return (dx < dy) ? x : y;
  }
  // init: top = {INF, INF, INF}, btm = {-INF, -INF, -INF}
  kdTree *nearest(const Point &p_, const Point &top, const Point &btm, int dep = 0) {
    Point ltop = top, rbtm = btm;
    ltop[dep] = p[dep];
    rbtm[dep] = p[dep];
    if (l == nullptr) {
      if (r == nullptr) return this;
      return nearer(p_, this, r->nearest(p_, top, rbtm, (dep+1)%DIM));
    } else if (r == nullptr) {
      return nearer(p_, this, l->nearest(p_, ltop, btm, (dep+1)%DIM));
    } else if (p[dep] > p_[dep]) {
      kdTree *near = l->nearest(p_, ltop, btm, (dep+1)%DIM);
      ld dist_now = dist(near->p - p_);
      ld dist_another = dist_pc(p_, top, rbtm);
      if (dist_another < dist_now) {
        kdTree *near2 = r->nearest(p_, top, rbtm, (dep+1)%DIM);
        ld dist2 = dist(near2->p - p_);
        if (dist2 < dist_now) return nearer(p_, this, near2);
        else return nearer(p_, this, near);
      } else {
        return nearer(p_, this, near);
      }
    } else {
      kdTree *near = r->nearest(p_, top, rbtm, (dep+1)%DIM);
      ld dist_now = dist(near->p - p_);
      ld dist_another = dist_pc(p_, ltop, btm);
      if (dist_another < dist_now) {
        kdTree *near2 = l->nearest(p_, ltop, btm, (dep+1)%DIM);
        ld dist2 = dist(near2->p - p_);
        if (dist2 < dist_now) return nearer(p_, this, near2);
        else return nearer(p_, this, near);
      } else {
        return nearer(p_, this, near);
      }
    }
  }
};
