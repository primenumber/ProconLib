template <class T>
ostream &operator<<(ostream &os, const vector<T> &v) {
  os << "[ ";
  for (auto it = v.begin(); it != v.end(); ++it) {
    if (it != v.begin()) os << ", ";
    os << *it;
  }
  os << " ]";
  return os;
}

template <class T, class U>
ostream &operator<<(ostream &os, const map<T,U> &m) {
  os << "{ ";
  for (auto it = m.begin(); it != m.end(); ++it) {
    if (it != m.begin()) os << ", ";
    os << "  " << it->first << " : " << it->second;
  }
  os << "}";
  return os;
}

template <class T>
ostream &operator<<(ostream &os, const set<T> &s) {
  os << "{ ";
  for (auto it = s.begin(); it != s.end(); ++it) {
    if (it != s.begin()) os << ", ";
    os << *it;
  }
  os << " }";
  return os;
}

template <class T, class U>
ostream &operator<<(ostream &os, const pair<T,U> &p) {
  os << "(" << p.first << ", " << p.second << ")";
  return os;
}
