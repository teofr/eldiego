int n,sq;
struct Qu{//queries [l, r) - intervalos cerrado abiertos !!! importante!!
    int l, r, id;
};
int ans[MAXN], curans;//ans[i]=ans to ith query
bool bymos(const Qu &a, const Qu &b){
    if(a.l/sq!=b.l/sq) return a.l<b.l;
    return (a.l/sq)&1? a.r<b.r : a.r>b.r;
}
void mos(vector<Qu> qs){
    forn(i, qs.size()) qs[i].id=i;
    sort(qs.begin(), qs.end(), bymos);
    int cl=0, cr=0; // Current left/right
    sq=sqrt(n);
    curans=0;
    for(auto &q : qs){ //intervalos cerrado abiertos !!! importante!!
        while(cl>q.l) add(--cl); // Agregar item al estado de la respuesta
        while(cr<q.r) add(cr++);
        while(cl<q.l) remove(cl++); // Sacar item del estado
        while(cr>q.r) remove(--cr);
        ans[q.id]=curans; // Calcular respuesta con los items actuales
    }
}
