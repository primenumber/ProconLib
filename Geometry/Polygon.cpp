P centroid(VP tri) {
  return (tri[0] + tri[1] + tri[2]) / (ld)3.0;
}

P incenter(VP tri) {
  ld l[3];
  REP(i,3) l[i] = abs(tri[(i+1)%3] - tri[(i+2)%3]);
  ld p = l[0]+l[1]+l[2];
  P ic;
  REP(i,3) ic += l[i]/p*tri[i];
  return ic;
}

