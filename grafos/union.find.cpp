struct UnionFind{
	vector<int> f;//the array contains the parent of each node
	void init(int n){f = vector<int>(n, -1);}
	int comp(int x){return (f[x]==-1?x:f[x]=comp(f[x]));}//O(1)
	bool join(int i, int j) { //O(1)
		bool con=comp(i)==comp(j);
		if(!con) f[comp(i)] = comp(j); //pa no romper la super complejidad
		return con;
	}};
