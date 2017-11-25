#include <bits/stdc++.h>
using namespace std;
#define dprint(v) cerr << #v"=" << v << endl //;)
#define forsn(i,a,b) for(int i=(a); i<(b); i++)
#define forn(i,n) forsn(i,0,n)
#define dforn(i,n) for(int i=n-1; i>=0; i--)
#define forall(it,v) for(auto it=v.begin();it!=v.end();++it)
#define sz(c) ((int)c.size())
#define zero(v) memset(v, 0, sizeof(v))
#define pb push_back
#define fst first
#define snd second
typedef long long tint;
typedef pair<int,int> ii;

#define MAXP 100000	//no necesariamente primo
int criba[MAXP+1];
void crearcriba(){
	int w[] = {4,2,4,2,4,6,2,6};
	for(int p=25;p<=MAXP;p+=10) criba[p]=5;
	for(int p=9;p<=MAXP;p+=6) criba[p]=3; 
	for(int p=4;p<=MAXP;p+=2) criba[p]=2;
	for(int p=7,cur=0;p*p<=MAXP;p+=w[cur++&7]) if (!criba[p]) 
		for(int j=p*p;j<=MAXP;j+=(p<<1)) if(!criba[j]) criba[j]=p;
}

vector<int> primos;
void buscarprimos(){
	crearcriba();
	forsn (i,2,MAXP+1) if (!criba[i]) primos.push_back(i);
}

//factoriza bien numeros hasta MAXP^2
map<tint,tint> fact(tint n){ //O (cant primos)
	map<tint,tint> ret;
	for(auto p : primos){
		while(!(n%p)){
			ret[p]++;//divisor found
			n/=p;
		}
	}
	if(n>1) ret[n]++;
	return ret;
}
//factoriza bien numeros hasta MAXP
map<tint,tint> fact2(tint n){ //O (lg n)
	map<tint,tint> ret;
	while (criba[n]){
		ret[criba[n]]++;
		n/=criba[n];
	}
	if(n>1) ret[n]++;
	return ret;
}
//Usar asi:  divisores(fac, divs, fac.begin()); NO ESTA ORDENADO
void divisores(const map<tint,tint> &f, vector<tint> &divs, map<tint,tint>::iterator it, tint n=1){
    if(it==f.begin()) divs.clear();
    if(it==f.end()) { divs.pb(n);  return; }
    tint p=it->fst, k=it->snd; ++it;
    forn(_, k+1) divisores(f, divs, it, n), n*=p;
}
tint sumDiv (tint n){
  tint rta = 1;
  map<tint,tint> f=fact(n);
  for(auto it : f) {
	tint pot = 1, aux = 0;  
	forn(i, it.snd+1) aux += pot, pot *= it.fst;
	rta*=aux;
  } 
  return rta;
}
tint eulerPhi (tint n){ // con criba: O(lg n)
  tint rta = n;
  map<tint,tint> f=fact(n);
  for(auto it : f) rta -= rta / it.first;
  return rta;
}
tint eulerPhi2 (tint n){ // O (sqrt n)
	tint r = n;
	forsn (i,2,n+1){
		if ((tint)i*i > n) break;
		if (n % i == 0){
			while (n%i == 0) n/=i;
			r -= r/i; }
	}
	if (n != 1) r-= r/n;
	return r;
}

int main() {
	buscarprimos();
	forsn (x,1, 500000){
		cout << "x = " << x << endl;
		//cout << "Numero de factores primos: " << numPrimeFactors(x) << endl;
		//cout << "Numero de distintos factores primos: " << numDiffPrimeFactors(x) << endl;
		//cout << "Suma de factores primos: " << sumPrimeFactors(x) << endl;
		//cout << "Numero de divisores: " << numDiv(x) << endl;
		cout << "Suma de divisores: " << sumDiv(x) << endl;
		cout << "Phi de Euler: " << eulerPhi(x) << endl;
	}
	return 0;
}

