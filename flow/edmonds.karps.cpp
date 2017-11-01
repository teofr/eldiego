#define MAX_V 1000
#define INF 1e9
//special nodes
#define SRC 0
#define SNK 1
const tint N = !!!;
vector<map<int, int>> G;//inicializar de tamaño n
//To add an edge use
void add(int a, int b, int w) {G[a][b]=w;}
int f; vector<int> p;
void augment(int v, int minE){
	if(v==SRC) f=minE;
	else if(p[v]!=-1){
		augment(p[v], min(minE, G[p[v]][v]));
		G[p[v]][v]-=f, G[v][p[v]]+=f;
	}
}
tint maxflow(){//O(VE^2)
	tint Mf=0;
	do{
		f=0;
		vector<char> used(N); queue<int> q; q.push(SRC);
		p = vector<char>(N, -1);
		while(sz(q)){
			int u=q.front(); q.pop();
			if(u==SNK) break;
			for(pp : G[u])
				if(pp.snd>0 && !used[pp.fst])
					used[pp.fst]=true, q.push(pp.fst), p[pp.fst]=u;
		}
		augment(SNK, INF);
		Mf+=f;
	}while(f);
	return Mf;
}
