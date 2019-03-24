const int MAXN=100000;
vector<ii> G[MAXN];
int n;

struct Ar{int a,b,w;}; //w y cost deberian tener el mismo tipo
bool operator<(const Ar& a, const Ar &b){return a.w<b.w;}
vector<Ar> E;
ll kruskal(){ //no hace falta agregar las aristas en las dos direcciones! (en prim si)
    ll cost=0;
    sort(E.begin(), E.end());//ordenar aristas de menor a mayor -- OJO cuando ordena algo no necesariamente las cosas del mismo valor quedan en el mismo orden!!
    uf.init(n);
    forall(it, E){
        if(uf.comp(it->a)!=uf.comp(it->b)){//si no estan conectados
            uf.join(it->a, it->b);//conectar
            cost+=it->w;
        }
    }
    return cost;
}
