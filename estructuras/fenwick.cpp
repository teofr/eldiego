//For 2D treat each column as a Fnwk T, by adding a nested for in each operatio
struct Fenwick{
	int sz; //los elementos van de 1 a sz-1
	tipo t[MAXN][MAXN];
	void init (int n){
		sz = n;
		forn(i,MAXN) forn(j,MAXN) t[i][j] = 0;
	}
	void adjust(int p, int q, tipo v){//suma v al valor de (p,q) -  O(lgn*lgn)
		for(int i=p; i<sz; i+=(i&-i)) //valid with p in [1, sz), q in [1,sz)
			for(int j=q; j<sz; j+=(j&-j)) t[i][j]+=v; }
	tipo sum(int p, int q){//cumulative sum in [(1,1), (p,q)], O(lgn*lgn)
	    tipo s=0; // OJO: los rangos son cerrados!
		for(int i=p; i; i-=(i&-i)) for(int j=q; j; j-=(j&-j)) s+=t[i][j];
		return s;
	}
	tipo sum(int a1, int b1, int a2, int b2){
		return sum(a2,b2)-sum(a1-1,b2) - sum(a2,b1-1) + sum(a1-1,b1-1);}
	//get largest value with cumulative sum less than or equal to x;
	//for smallest, pass x-1 and add 1 to result. Values must be all positive
	int getind(tipo x) {//O(lgn)
	  	int idx = 0, mask = 1<<(32-__builtin_clz(sz));
	  	while(mask && idx < sz) {
	   		int v = idx + mask;
			if(x >= t[v]) {idx = v, x -= t[v];}
	   		mask >>= 1; }
	  	return idx;
	}} f;
