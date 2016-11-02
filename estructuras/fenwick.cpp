//For 2D threat each column as a Fenwick tree, by adding a nested for in each operation
struct Fenwick{
	int sz; //los elementos van de 1 a sz-1
	tipo t[MAXN][MAXN];
	void init (int n){
		sz = n;
		forn(i,MAXN) forn(j,MAXN) t[i][j] = 0;
	}
	//le suma v al valor de (p,q)
	void adjust(int p, int q, tipo v){//valid with p in [1, sz), q in [1,sz) --> O(lgn*lgn)
		for(int i=p; i<sz; i+=(i&-i)) 
			for(int j=q; j<sz; j+=(j&-j))
				t[i][j]+=v; }
	tipo sum(int p, int q){//cumulative sum in [(1,1), (p,q)], O(lgn*lgn) -- OJO: los rangos son cerrados!
		tipo s=0;
		for(int i=p; i; i-=(i&-i)) for(int j=q; j; j-=(j&-j)) s+=t[i][j];
		return s;
	}
	tipo sum(int a1, int b1, int a2, int b2){return sum(a2,b2)-sum(a1-1,b2) - sum(a2,b1-1) + sum(a1-1,b1-1);}
	//get largest value with cumulative sum less than or equal to x;
	//for smallest, pass x-1 and add 1 to result
	int getind(tipo x) {//O(lgn) -- VER!
	  	int idx = 0, mask = N;
	  	while(mask && idx < N) {
	   		int t = idx + mask;
			if(x >= tree[t])
		  		idx = t, x -= tree[t];
	   		mask >>= 1;
	  	}
	  	return idx;
	}} f;
