//Dado un arreglo y una operacion asociativa con neutro, get(i, j) opera sobre el rango [i, j).
typedef int Elem;//Elem de los elementos del arreglo
typedef int Alt;//Elem de la alteracion
#define operacion(x,y) x+y
const Elem neutro=0; const Alt neutro2=0;
#define MAXN 1024000
struct RMQ{
	int sz;
	Elem t[4*MAXN];
	Alt dirty[4*MAXN];//las alteraciones pueden ser de distinto Elem
	Elem &operator[](int p){return t[sz+p];}
	void init(int n){//O(nlgn)
		sz = 1 << (32-__builtin_clz(n));
		forn(i, 2*sz) t[i]=neutro;
		forn(i, 2*sz) dirty[i]=neutro2;
	}
	void updall(){//O(n)
		dforn(i, sz) t[i]=operacion(t[2*i], t[2*i+1]);}
	void opAltT(int n,int a,int b){//altera el valor del nodo n segun su dirty y el intervalo que le corresponde.
			t[n] += dirty[n]*(b-a); //en este caso la alteracion seria sumarle a todos los elementos del intervalo [a,b) el valor dirty[n]
		}
	void opAltD(int n ,Alt val){
		dirty[n]+= val;
		}//actualiza el valor de Dirty "sumandole" val. podria cambiar el valor de dirty dependiendo de la operacion que se quiera al actualizar un rango. Ej:11402.cpp
	void push(int n, int a, int b){//propaga el dirty a sus hijos
		if(dirty[n]!=neutro2){
			//t[n]+=dirty[n]*(b-a);//altera el nodo 
			opAltT(n,a,b); 
			if(n<sz){
				opAltD(2*n,dirty[n]);//dirty[2*n]+=dirty[n];
				opAltD(2*n+1,dirty[n]);//dirty[2*n+1]+=dirty[n];
			}
			dirty[n]=neutro2;
		}
	}
	Elem get(int i, int j, int n, int a, int b){//O(lgn)
		if(j<=a || i>=b) return neutro;
		push(n, a, b);//corrige el valor antes de usarlo
		if(i<=a && b<=j) return t[n];
		int c=(a+b)/2;
		return operacion(get(i, j, 2*n, a, c), get(i, j, 2*n+1, c, b));
	}
	Elem get(int i, int j){return get(i,j,1,0,sz);}
	//altera los valores en [i, j) con una alteracion de val
	void alterar(Alt val, int i, int j, int n, int a, int b){//O(lgn)
		push(n, a, b);
		if(j<=a || i>=b) return;
		if(i<=a && b<=j){
			opAltD(n ,val);//actualiza el valor de Dirty por val.
			push(n, a, b);
			return;//este nodo esta totalmente contenido por el intervalo a alterar, no es necesario que se lo pases a los hijos.. por ahora..
		}
		int c=(a+b)/2;
		alterar(val, i, j, 2*n, a, c), alterar(val, i, j, 2*n+1, c, b);
		t[n]=operacion(t[2*n], t[2*n+1]);//por esto es el push de arriba
	}
	void alterar(Alt val, int i, int j){alterar(val,i,j,1,0,sz);}
};
