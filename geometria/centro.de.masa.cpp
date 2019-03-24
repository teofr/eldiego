usa: vector, forn
struct pto { tint x,y; };
typedef vector<pto> poly;
tint pcruz(tint x1, tint y1, tint x2, tint y2) { return x1*y2-x2*y1; }
tint area3(const pto& p, const pto& p2, const pto& p3) {
  return pcruz(p2.x-p.x, p2.y-p.y, p3.x-p.x, p3.y-p.y);
}
tint areaPor2(const poly& p) {
  tint a = 0; tint l = p.size()-1;
  forn(i,l-1) a += area3(p[i], p[i+1], p[l]);
  return abs(a);
}
pto bariCentroPor3(const pto& p1, const pto& p2, const pto& p3) {
  pto r;
  r.x = p1.x+p2.x+p3.x; r.y = p1.y+p2.y+p3.y;
  return r;
}
struct ptoD { double x,y; };
  ptoD centro(const poly& p) {
    tint a = 0; ptoD r; r.x=r.y=0; tint l = p.size()-1;
    forn(i,l-1) {
      tint act = area3(p[i], p[i+1], p[l]);
      pto pact = bariCentroPor3(p[i], p[i+1], p[l]);
      r.x += act * pact.x; r.y += act * pact.y; a += act;
  } r.x /= (3 * a); r.y /= (3 * a); return r;
}
//Area ellipse = M_PI*a*b where a and b are the semi axis lengths
//Area triangle = sqrt(s*(s-a)(s-b)(s-c)) where s=(a+b+c)/2
