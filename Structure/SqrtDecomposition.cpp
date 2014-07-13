typedef int Data;

const int num = 500;

const Data identity = 1000000000;
Data merge(Data a, Data b) {
  return min(a, b);
}

class RangeMinimumQuery {
private:
  int renewCount;
  vector<vector<Data>> dat;
  vector<Data> mindat;
  void renew(int n) {
    Data mi = identity;
    for (int i = 0; i < dat[n].size(); i++)
      mi = merge(mi, dat[n][i]);
    mindat[n] = mi;
  }
  void smooth(void) {
    vector<Data> v;
    for (int i = 0; i < num; i++)
      for (int j = 0; j < dat[i].size(); j++)
        v.push_back(dat[i][j]);
    dat = vector<vector<Data>>(num);
    for (int i = 0; i < v.size(); i++) dat[i/num].push_back(v[i]);
    for (int i = 0; i < num; i++) renew(i);
  }
  pair<int,int> place(int n) {
    int cnt = 0;
    for (int i = 0; i < num; i++) {
      if (cnt + dat[i].size() > n)
        return make_pair(i, n - cnt);
      cnt += dat[i].size();
    }
    assert(false);
    return make_pair(0, 0);
  }
public:
  RangeMinimumQuery(const vector<Data> &v) {
    dat.resize(num); mindat.resize(num);
    dat[0] = v; smooth();
    renewCount = num;
  }
  void update(int pos, int val) {
    pair<int,int> p = place(pos);
    dat[p.first][p.second] = val;
    renew(p.first);
  }
  void insert(int p, Data val) {
    pair<int,int> pos = place(p);
    dat[pos.first].insert(dat[pos.first].begin() + pos.second, val);
    if (--renewCount <= 0) { smooth(); renewCount = num; }
    else { renew(pos.first); }
  }
  void erase(int p) {
    pair<int,int> pos = place(p);
    dat[pos.first].erase(dat[pos.first].begin() + pos.second);
    if (--renewCount <= 0) { smooth(); renewCount = num; }
    else { renew(pos.first); }
  }
  void rotate(int l, int r) { // closed interval
    pair<int,int> lpos = place(l), rpos = place(r);
    Data val = dat[rpos.first][rpos.second];
    dat[rpos.first].erase(dat[rpos.first].begin() + rpos.second);
    dat[lpos.first].insert(dat[lpos.first].begin() + lpos.second, val);
    if (--renewCount <= 0) { smooth(); renewCount = num; }
    else { renew(lpos.first); renew(rpos.first); }
  }
  Data value(int pos) {
    pair<int,int> p = place(pos);
    return dat[p.first][p.second];
  }
  Data minimum(int l, int r) { // closed interval
    pair<int,int> lpos = place(l), rpos = place(r);
    Data mi = identity;
    if (lpos.first == rpos.first) {
      for (int i = lpos.second; i <= rpos.second; i++)
        mi = merge(mi, dat[lpos.first][i]);
    }
    else {
      for (int i = lpos.second; i < dat[lpos.first].size(); i++)
        mi = merge(mi, dat[lpos.first][i]);
      for (int i = lpos.first + 1; i < rpos.first; i++)
        mi = merge(mi, mindat[i]);
      for (int i = 0; i <= rpos.second; i++)
        mi = merge(mi, dat[rpos.first][i]);
    }
    return mi;
  }
};
