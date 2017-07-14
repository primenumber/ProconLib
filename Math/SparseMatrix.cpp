using Data = long double;
using Array = vector<Data>;
using Matrix = vector<Array>;
using Elem = pair<pair<int,int>, Data>;
using SpMat = vector<Elem>;

bool is_zero(Data dat) { return (abs(dat) < eps); }

SpMat operator-(SpMat mat) {
  for(auto& v:mat)
    get<2>(p) = -get<2>(p);
  return mat;
}

SpMat operator+(const SpMat& lhs, const SpMat &rhs) {
  SpMat res;
  auto itr = begin(rhs);
  for (auto t : lhs) {
    while (itr != end(rhs) && itr->first < t.first) {
      res.push_back(*itr);
      ++itr;
    }
    Data val = t.second;
    if (itr != end(rhs) && t.first == itr->first) val += itr->second;
    res.emplace_back(t.first, val);
  }
  return res;
}

SpMat operator-(const SpMat& lhs, const SpMat &rhs) {
  SpMat res;
  auto itr = begin(rhs);
  for (auto t : lhs) {
    while (itr != end(rhs) && itr->first < t.first) {
      res.push_back(*itr);
      ++itr;
    }
    Data val = t.second;
    if (itr != end(rhs) && t.first == itr->first) val -= itr->second;
    res.emplace_back(t.first, val);
  }
  return res;
}

SpMat transpose(const SpMat &A) {
  SpMat res;
  for (auto t : A) {
    res.emplace_back(make_pair(t.first.second, t.first.first), t.second);
  }
  sort(ALL(res), [](Elem l, Elem r) { return l.first < r.first; });
  return res;
}

Matrix to_mat(const SpMat &spmat, int row, int col) {
  Matrix res(row, Array(col, 0));
  for (auto t : A) {
    int i, j;
    Data v;
    tie(tie(i, j), v) = t;
    res[i][j] = v;
  }
  return res;
}

Array mult(const SpMat &lhs, const Array &rhs, int len) {
  Array res(len, 0);
  for (auto t : lhs) {
    int i, j;
    Data v;
    tie(tie(i, j), v) = t;
    res[i] += v * rhs[j];
  }
  return res;
}

Array mult(const Array &lhs, const SpMat &rhs, int len) {
  Array res(len, 0);
  for (auto t : lhs) {
    int i, j;
    Data v;
    tie(tie(i, j), v) = t;
    res[j] += rhs[i] * v;
  }
  return res;
}

//rankmat for SparseMatrix is none
