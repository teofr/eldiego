#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>
#include <cstring>
using namespace std;
#define dforn(i, n) for(int i=(n)-1; i>=0; i--)
#define forr(i, a, b) for(int i=(a); i<(b); i++)
#define forn(i, n) forr(i, 0, n)
#define sz(v) ((int)v.size())
#define zero(v) memset(v, 0, sizeof(v));
#define forall(it,v) for(typeof(v.begin()) it=v.begin();it!=v.end();++it)
#define INF 1e9
typedef pair<int, int> ii;
const int MAXN=100100;

int d1[MAXN];//d1[i]=long del maximo palindromo impar con centro en i
int d2[MAXN];//d2[i]=analogo pero para longitud par
//a a b c c <--d1[2]=5
//a a b b <--d2[2]=4 (estan uno antes)
void manacher(string &s){
	int l=0, r=-1, n=s.size();
	forn(i, n){
		int k=(i>r? 1 : min(d1[l+r-i], r-i));
		while(i+k<n && i-k>=0 && s[i+k]==s[i-k]) ++k;
		d1[i] = k--;
		if(i+k > r) l=i-k, r=i+k;
	}
	l=0, r=-1;
	forn(i, n){
		int k=(i>r? 0 : min(d2[l+r-i+1], r-i+1))+1;
		while(i+k-1<n && i-k>=0 && s[i+k-1]==s[i-k]) k++;
		d2[i] = --k;
		if(i+k-1 > r) l=i-k, r=i+k-1;
	}
	forn(i,n) { // Traducir los resultados a tamanio total del palindromo
		d1[i] = d1[i] * 2 - 1;
		d2[i] = d2[i] * 2;
	}}

int main(){
	while(cin >> s){
		manacher(s);
		forn(i, sz(s)) cout << d1[i] << ' '; cout << endl;
		forn(i, sz(s)) cout << d2[i] << ' '; cout << endl;
	}
	return 0;
}
