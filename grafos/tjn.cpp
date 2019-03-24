#define MAX 10010

vector<int> G[MAX];

//idx[i]=index assigned in the dfs
//lw[i]=lowest index(closer from the root) reachable from i
int lw[MAX], idx[MAX], qidx;
stack<int> q;
int qcmp, cmp[MAX];


void init(){
	zero(G);
	memset(idx, 0, sizeof(idx)), qidx=0;
	memset(cmp, -1, sizeof(cmp)), qcmp=0;
	
	}
//OJO! las componentes van de 1 a qcmp!
void tjn(int v){//O(V+E)
	lw[v]=idx[v]=++qidx;
	q.push(v), cmp[v]=-2;
	forall(it, G[v]){
		if(!idx[*it] || cmp[*it]==-2){
			if(!idx[*it]) tjn(*it);
			lw[v]=min(lw[v], lw[*it]);
		}
	}
	if(lw[v]==idx[v]){//(* O(V) amortizado -- cada vertice pertenece a una sola componente fuertemente conexa
		qcmp++;
		//int flag = 1; (para imprimir)
		int x;
		do{
			x=q.top(); q.pop(); 
			cmp[x]=qcmp;
			/*if(!flag) cout <<", ";
			else flag = 0;
			cout << x;*/
			}while(x!=v);
		//cout << endl;
	}
}
