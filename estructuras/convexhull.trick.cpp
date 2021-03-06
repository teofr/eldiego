#include <bits/stdc++.h>
#include <unistd.h>
using namespace std;
#define dprint(v) cerr << #v"=" << v << endl //;)
#define forr(i,a,b) for(int i=(a); i<(b); i++)
#define forn(i,n) forr(i,0,n)
#define dforn(i,n) for(int i=n-1; i>=0; i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();++it)
#define pb push_back
#define fst first
#define snd second
typedef long long ll;
typedef pair<int,int> ii;
typedef ll tipo;

struct Line{tipo m,h;};
tipo inter(Line a, Line b){
    // guarda que se rompe con paralelas. ni idea con misma linea
    tipo x=b.h-a.h, y=a.m-b.m;
    return x/y+(x%y?!((x>0)^(y>0)):0);//==ceil(x/y)
}
struct CHT {
	vector<Line> c;
	bool mx;
	int pos;
	CHT(bool mx=0):mx(mx),pos(0){}//mx=1 si las query devuelven el max
    //Creo que te da la iesima con m mas grande
	inline Line acc(int i){return c[c[0].m>c.back().m? i : c.size()-1-i];}
	inline bool irre(Line x, Line y, Line z){
		return c[0].m>z.m? inter(y,z) <= inter(x,y) : inter(y,z) >= inter(x,y);}
	void add(tipo m, tipo h) {//O(1) amortiz, los m tienen que entrar ordenados
    if(mx) m*=-1, h*=-1;
    Line l=(Line){m, h};
    if(c.size() && m==c.back().m) {
			l.h=min(h, c.back().h), c.pop_back(); if(pos) pos--; }
    while(c.size()>=2 && irre(c[c.size()-2], c[c.size()-1], l)) {
			c.pop_back(); if(pos) pos--; }
    c.pb(l);
	} //fbin: esta x en el bin m o antes?
	inline bool fbin(tipo x, int m) {return inter(acc(m), acc(m+1))>x;}
	tipo eval(tipo x){//query con x no ordenados O(lgn)
		int n = c.size();
		int a=-1, b=n-1;
		while(b-a>1) { int m = (a+b)/2;
			if(fbin(x, m)) b=m;
			else a=m;}
		return (acc(b).m*x+acc(b).h)*(mx?-1:1); //query O(1) amortizado
		while(pos>0 && fbin(x, pos-1)) pos--;
		while(pos<n-1 && !fbin(x, pos)) pos++;
		return (acc(pos).m*x+acc(pos).h)*(mx?-1:1);
	}} ch;



struct CHTBruto {
	vector<Line> c;
	bool mx;
	CHTBruto(bool mx=0):mx(mx){}//mx=si las query devuelven el max o el min
	void add(tipo m, tipo h) { //O(1)
		Line l=(Line){m, h};
        c.pb(l);
	}
	tipo eval(tipo x){ //O(n)
        tipo r=c[0].m*x+c[0].h;
        forn(i, sz(c)) if(mx) r=max(r, c[i].m*x+c[i].h);
                       else r=min(r, c[i].m*x+c[i].h);
        return r;
	}
} chb;

#define RND(a, b) (rand()%((b)-(a)+1)+(a))
#define MAXM 10000
#define MINIT RND(-1000, 1000)
#define MSTEP RND(0, 10)

#define HVAL RND(-1000, 1000)
#define XVAL RND(-1000, 1000)
#define MAXSZ 1000000

int main() {
    tipo m,h,x;
    int t;
    int dir;
    int seed=time(NULL);
    srand(seed);
    for(int tc=0; ; tc++){ reset:
        t=0;
        t=rand()%2;
        dir=-1;
        dir=rand()%2?1:-1;
        m=MINIT;
        if(!m) m++;
        cout << "CLEAR, QUERY " << (t?"MAX":"MIN") << endl;
        ch=CHT(t), chb=CHTBruto(t);
        forn(_, 25){
            m=m+dir*MSTEP;
            if(!m) m+=dir;
            if(m>MAXM) goto reset;
            h=HVAL;
            cout << "ADD " << m << ' ' << h << endl;
            ch.add(m, h);
            chb.add(m, h);
        }
        x=XVAL;
        tipo v=ch.eval(x);
        tipo b=chb.eval(x);
        cout << "QUERY " << x << ' ' << v << ' ' << b << endl;
        assert(v==b || !(dprint(seed)));
    }
    return 0;
}
