#define MOD 1000000000000000009
#define PRIME 1009

struct mnum{
	static const tipo mod=MOD;
	tipo v;
	mnum(tipo v=0): v(v%mod) {}
	mnum operator+(mnum b){return (v+b.v)%mod;}
	mnum operator-(mnum b){return (((v-b.v)%mod)+mod)%mod;}
	mnum operator*(mnum b){return mul(v,b.v,mod);}
	mnum operator^(int n){
		if(!n) return 1;
		return n%2 ? ((*this)^(n/2))*(*this) : (*this)^(n/2);}
};
