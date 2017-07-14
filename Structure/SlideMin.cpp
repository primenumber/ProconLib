using Data = int;

struct SlideMin {
  deque<pair<int,Data>> deq;
  int c, w;
  SlideMin(int w) : c(0), w(w) {;}
  Data query(Data d) {
    ++c;
    while (!deq.empty() && deq.front().first <= c - w) deq.pop_front();
    while (!deq.empty() && deq.back().second >= d) deq.pop_back();
    deq.push_back(make_pair(c, d));
    return deq.front().second;
  }
};
