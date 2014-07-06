
// Regular Octahedron
// 1 2 3 4
// 7 8 5 6

class RegularOctahedron {
public:
  int face[8];
  void roll(int a, int b, int c, int d,
	    int e, int f, int g, int h) {
    int atemp = face[a], etemp = face[e];
    face[a] = face[d]; face[d] = face[c]; face[c] = face[b]; face[b] = atemp;
    face[e] = face[h]; face[h] = face[g]; face[g] = face[f]; face[f] = etemp;
  }
  void rollX(void) { roll(4, 0, 3, 7, 5, 1, 2, 6); }
  void rollY(void) { roll(0, 4, 5, 1, 3, 7, 6, 2); }
  void rollZ(void) { roll(0, 1, 2, 3, 4, 5, 6, 7); }

  bool equivalentTo(const Dice& d) {
    for (int k = 0; k < 6; (k&1?rollY():rollX()),++k) {
      for (int i = 0; i < 4; rollZ(), ++i) {
	bool ok = true;
	REP(i, 8) if(this->face[i] != d.face[i]) {ok = false; break;}
	if (ok) return true;
      }
    }
    return false;
  }
  bool operator<(const Dice& d) const {
    REP(i, 8) {
      if(this->face[i] < d.face[i]) return true;
      if(this->face[i] > d.face[i]) return false;
    }
    return false;
  }
  bool operator==(const Dice& d) {
    return this->equivalentTo(d);
  }
};
