const int MAXN=1010;
int n, m;
vector<int> G[MAXN];

struct edge {
	int u,v, comp;
	bool bridge;
};
vector<edge> e;
void addEdge(int u, int v) {
	G[u].pb(sz(e)), G[v].pb(sz(e));
	e.pb((edge){u,v,-1,false});
}
//V[i]=id de la dfs
//L[i]=lowest id reachable from i
int V[MAXN], L[MAXN], qV;
int nbc;//cant componentes
int comp[MAXN];//comp[i]=cant comp biconexas a la cual pertenece i
void initDfs(int n) {
	zero(G), zero(comp);
	e.clear();
	forn(i,n) V[i]=-1;
	nbc = qV = 0;
}
stack<int> st;
void dfs(int u, int pe) {//O(n + m)
    L[u] = V[u] = qV++;
	comp[u] = (pe != -1);
    forall(ne, G[u]) if (*ne != pe){
		int v = e[*ne].u ^ e[*ne].v ^ u; // x ^ y ^ x = y!
		if (V[v] == -1) { // todavia no se lo visito
			st.push(*ne);
			dfs(v,*ne);
			if (L[v] > V[u]){// bridge => no pertenece a ninguna comp biconexa
				e[*ne].bridge = true; 
			}
			if (L[v] >= V[u]){ // art
				int last;
				do { //todas las aristas que estan entre dos puntos de articulacion pertenecen a la misma componente biconexa
					last = st.top(); st.pop();
					e[last].comp = nbc;
				} while (last != *ne); 
				nbc++;
				comp[u]++;
			}
			L[u] = min(L[u], L[v]);
		}
		else if (V[v] < V[u]) { // back edge
			st.push(*ne);
			L[u] = min(L[u], V[v]);
		}
	}
}

int main() {
	while(cin >> n >> m){
		initDfs(n);
		forn(i, m){
			int a,b; cin >> a >> b;
			addEdge(a,b);
		}
        dfs(0,-1);		
        forn(i, n) cout << "comp[" << i << "] = " <<  comp[i] << endl;
		forall(ne, e) cout << ne->u << "->" << ne->v << " en la comp. " << ne->comp << endl;
		cout << "Cant. de componentes biconexas = " << nbc << endl;
	}
    return 0;
}

