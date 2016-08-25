int N;
vector<int> G[1000000];
//V[i]=node number(if visited), L[i]= lowest V[i] reachable from i
int qV, V[1000000], L[1000000], P[1000000];
void dfs(int v, int f){
	L[v]=V[v]=++qV;
	forall(it, G[v])
		if(!V[*it]){
			dfs(*it, v);
			L[v] = min(L[v], L[*it]); //a todo lo que pueden llegar mis hijos yo tmb puede llegar
			P[v]+= L[*it]>=V[v]; // no puede llegar a ningun vertice u / V[u] < V[v] => si saco v quedan desconectados => v punto de articulacion
		}
		else if(*it!=f) //backedge 
			L[v]=min(L[v], V[*it]);
}
int cantart(int N){ //O(n)
	qV=0;
	zero(V), zero(P);
	dfs(0, -1); 
    P[0]--; //la raiz debe tener al menos dos hijos para ser punto de articulazion
	int q=0;
	forn(i, N) if(P[i]) q++;
return q;
}

