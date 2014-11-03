// Verified : AOJ2535
struct card {
  int suit, rank;
  card(const string& s) {
    suit = string("CDHS").find(s[0]);
    rank = string("0A23456789TJQK").find(s[1]);
  }
  bool operator<(const card& o) const {
    return rank != o.rank ? rank < o.rank : suit < o.suit;
  }
};
 
int poker_hand(const vector<card>& hand) {
  vector<int> X(27), Y(4);
  for (card i : hand) {
    ++X[i.rank]; ++Y[i.suit];
    if (i.rank == 1) ++X[i.rank+13]; // for wrapping
  }
  bool straight = false;
  for (int i = 1; i+4 < 27; ++i) // wrapping range
    if (X[i+0] && X[i+1] && X[i+2] && X[i+3] && X[i+4]) straight = true;
  X[1] = 0; sort(X.rbegin(), X.rend()); sort(Y.rbegin(), Y.rend());
  bool flush = (Y[0] == 5);
  if (straight) return (flush ? 8 : 4);
  if (flush) return 5;
  if (X[0] == 4) return 7;
  if (X[0] == 3) return (X[1] == 2 ? 6 : 3);
  if (X[0] == 2) return (X[1] == 2 ? 2 : 1);
  return 0;
}
 
vector<int> sort_hands(const vector<card>& hand, bool ace) {
  int N = hand.size();
  vector<pair<int,int>> vec(N);
  REP(i,N) {
    int cnt = 0, num = hand[i].rank;
    for (card c : hand) if (num == c.rank) ++cnt;
    vec[i] = make_pair(cnt, num);
  }
  REP(i,N) if (vec[i].second == 1 && ace) vec[i].second = 14;
  sort(vec.rbegin(), vec.rend());
  vector<int> res(N);
  REP(i,N) res[i] = vec[i].second;
  return res;
}
 
int poker(const vector<card>& hand) {
  int a = poker_hand(hand);
  bool flag = ((a != 4 && a != 8) || hand[0].rank > 8 || hand[1].rank > 8);
  vector<int> vec = sort_hands(hand, flag);
  int res = (a << 20);
  REP(i,5) res += (vec[i] << ((4 - i) * 4));
  return res;
}
