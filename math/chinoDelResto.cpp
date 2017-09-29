struct dxy {tint d,x,y;};
dxy mcde(tint a, tint b) {
    dxy r, t;
    if (b == 0) {
        r.d = a; r.x = 1; r.y = 0;
    } else {
        t = mcde(b,a %b);
        r.d = t.d; r.x = t.y;
        r.y = t.x - a/b*t.y;
    }
    return r;
}
tint modq(x, q) { return (x % q + q) % q ; }
tint tcr(tint* r, tint* m, int n) {
    tint p=0, q=1;
    forn(i, n) {
        p = modq(p-r[i], q);
        dxy w = mcde(m[i], q);
        if (p % w.d) return -1; // sistema incompaible
        q = q / w.d * m[i];
        p = modq(r[i] + m[i] * p / w.d * w.x, q);
    }
    return p; // x \equiv p (q)
}
