#include <vector>
#include <cstring>
using namespace std;
typedef long long tint;
#define forall(it,v) for(auto it=v.begin();it!=v.end();++it)
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define sz(v) ((int)v.size())
#define INF 1e18

const int MAX = 300;
// Corte minimo: vertices con dist[v]>=0 (del lado de src) VS.  dist[v]==-1 (del lado del dst)
// Para el caso de la red de Bipartite Matching (Sean V1 y V2 los conjuntos mas proximos a src y dst respectivamente):
// Reconstruir matching: para todo v1 en V1 ver las aristas a vertices de V2 con it->f>0, es arista del Matching
// Min Vertex Cover: vertices de V1 con dist[v]==-1 + vertices de V2 con dist[v]>0
// Max Independent Set: tomar los vertices NO tomados por el Min Vertex Cover
// Max Clique: construir la red de G complemento (debe ser bipartito!) y encontrar un Max Independet Set
// Min Edge Cover: tomar las aristas del matching + para todo vertices no cubierto hasta el momento, tomar cualquier arista de el
//Complejidad: 
//Peor caso: O(V^2E)
//Si todas las capacidades son 1: O(min(E^1/2,V^2/3)E)
//Para matching bipartito es: O(sqrt(V)E)

int nodes, src, dst; // Setear estos
vector<int> dist, q, work; // inicializar de tamaño n
struct Edge {
    int to, rev;
    tint f, cap;
    Edge(int to, int rev, tint f, tint cap) : to(to), rev(rev), f(f), cap(cap) {}
};
vector<vector<Edge>> G; // inicializar de tamaño n
void addEdge(int s, int t, tint cap){
    G[s].pb(Edge(t, G[t].size(), 0, cap)); G[t].pb(Edge(s, G[s].size(), 0, 0));}
bool dinic_bfs(){
    for(auto & c : dist) c = -1;
    dist[src]=0;
    int qt=0; q[qt++]=src;
    for(int qh=0; qh<qt; qh++){
        int u =q[qh];
        for(auto &e : G[u]){
            int v=e.to;
            if(dist[v]<0 && e.f < e.cap)
                dist[v]=dist[u]+1, q[qt++]=v;
        }
    }
    return dist[dst]>=0;
}
tint dinic_dfs(int u, tint f){
    if(u==dst) return f;
    for(int &i=work[u]; i<G[u].size(); i++){
        Edge &e = G[u][i];
        if(e.cap<=e.f) continue;
        int v=e.to;
        if(dist[v]==dist[u]+1){
                tint df=dinic_dfs(v, min(f, e.cap-e.f));
                if(df>0){
                        e.f+=df; G[v][e.rev].f-= df;
                        return df;  }
        }
    }
    return 0;
}
tint maxFlow(int _src, int _dst){
    src=_src, dst=_dst;
    tint result=0;
    while(dinic_bfs()){
        for(auto & c : work) c = 0;
        while(tint delta=dinic_dfs(src,INF))
            result+=delta;
    }
    // todos los nodos con dist[v]!=-1 vs los que tienen dist[v]==-1 forman el min-cut
    return result; }
