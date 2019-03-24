#define INF 1e9
#define MAX_N 1001
vector<ii> G[MAX_N];//ady. list with pairs (weight, dst)
//To add an edge use
#define add(a, b, w) G[a].pb(make_pair(w, b))
int dist[MAX_N];
int N; //cantidad de vertices -- setear!!
void bford(int src){//O(VE)
	memset(dist,INF,sizeof dist);
	dist[src]=0;
	forn(i, N-1) forn(j, N) if(dist[j]!=INF) forall(it, G[j])
		dist[it->snd]=min(dist[it->snd], dist[j]+it->fst);
}

bool hasNegCycle(){
	forn(j, N) if(dist[j]!=INF) forall(it, G[j])
		if(dist[it->snd]>dist[j]+it->fst) return true;
	//inside if: all points reachable from it->snd will have -INF distance(do bfs) ?
	return false;
}
