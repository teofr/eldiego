#define MAXN 1005
#define MAXE 1005005

int n,ars[MAXE], eq;
vector<int> G[MAXN];//fill G,ars,eq
list<int> path;
int used[MAXN]; //used[v] = i => para todo j<=i la arista v-G[v][j] fue usada y la arista v-G[v][i+1] no se uso
bool usede[MAXE];

//encuentra el ciclo euleriano, el grafo debe ser conexo y todos los nodos tener grado par para que exista
//para encontrar el camino euleriano conectar los dos vertices de grado impar y empezar de uno de ellos.

queue<list<int>::iterator> q;
int get(int v){
	while(used[v]<sz(G[v]) && usede[ G[v][used[v]] ]) used[v]++;
	return used[v];
}
void explore(int v, int r, list<int>::iterator it){
	int ar=G[v][get(v)]; int u=v^ars[ar];
	usede[ar]=true;
	list<int>::iterator it2=path.insert(it, u);
	if(u!=r) explore(u, r, it2);
	if(get(v)<sz(G[v])) q.push(it);
}
void euler(int a){ 
	zero(used), zero(usede);
	path.clear();
	q=queue<list<int>::iterator>();
	path.push_back(a); q.push(path.begin());
	while(sz(q)){
		list<int>::iterator it=q.front(); q.pop();
		if(used[*it]<sz(G[*it])) explore(*it, *it, it);
	}
	reverse(path.begin(), path.end());
}
void addEdge(int u, int v){
	G[u].pb(eq), G[v].pb(eq);
	ars[eq++]=u^v;
}
