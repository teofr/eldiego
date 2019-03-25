#define MAX_N 112345
#define rBOUND(x) ((x) < n ? r[(x)] : 0)
//sa will hold the suffixes in order.
int sa[MAX_N], r[MAX_N], n;// OJO n = s.size()!
string s; //input string, n=s.size()

vector<int> f, tmpsa;
void countingSort(int k){
	f.clear(); f.resize(n);
	forn(i, n) f[rBOUND(i+k)]++;
	int sum=0;
	forn(i, max(255, n)){ int t=f[i]; f[i]=sum; sum+=t;}
	forn(i,n) tmpsa[f[rBOUND(sa[i]+k)]++]=sa[i];
	forn(i,n) sa[i] = tmpsa[i];
}
void constructsa(){//O(n log n)
	n = s.size();
 	tmpsa.clear(); tmpsa.resize(n);
	forn(i,n) {sa[i]=i, r[i]=s[i];}
	for(int k=1; k<n; k<<=1){
		countingSort(k), countingSort(0);
		int rank
		vector<int>tmpr(n);
		tmpr[sa[0]]=rank=0;
		forr(i, 1, n)
			tmpr[sa[i]] = (r[sa[i]]==r[sa[i-1]] && r[sa[i]+k]==r[sa[i-1]+k]) ?
				rank : ++rank;
		forn(i,n) r[i]=tmpr[i];
		if(r[sa[n-1]]==n-1) break;
	}
}
void print(){//for debugging
	forn(i, n)
		cout << i << ' ' <<
		s.substr(sa[i], s.find('$',sa[i])-sa[i]) << endl;}

//returns [lowerbound, upperbound] of the search -- extremos estan incluidos!
ii stringMatching(string P){ //O(sz(P)lgn)
	int lo=0, hi=n-1, mid=lo;
	while(lo<hi){
		mid=(lo+hi)/2;
		int res=s.compare(sa[mid], P.size(), P);
		if(res>=0) hi=mid;
		else lo=mid+1;
	}
	if(s.compare(sa[lo], P.size(), P)!=0) return {-1, -1};
	ii ans; ans.fst=lo;
	lo=0, hi=n-1, mid;
	while(lo<hi){
		mid=(lo+hi)/2;
		int res=s.compare(sa[mid], P.size(), P);
		if(res>0) hi=mid;
		else lo=mid+1;
	}
	if(s.compare(sa[hi], P.size(), P)!=0) hi--;
	ans.snd=hi;
	return ans;
}

//Calculates the LCP between consecutive suffixes in the Suffix Array.
//LCP[i] is the length of the LCP between sa[i] and sa[i-1]
int LCP[MAX_N], phi[MAX_N], PLCP[MAX_N];
void computeLCP(){//O(n) - Longest common prefix
	phi[sa[0]]=-1;
	forsn(i, 1, n) phi[sa[i]]=sa[i-1];
	int L=0;
	forn(i, n){
		if(phi[i]==-1) {PLCP[i]=0; continue;}
		while(s[i+L]==s[phi[i]+L]) L++;
		PLCP[i]=L;
		L=max(L-1, 0);
	}
	forn(i, n) LCP[i]=PLCP[sa[i]];
}

//usage
int main() {
    cin>>s;
    s.pb('$');
    constructsa();
    computeLCP();
    
    //usar...

    zero(phi); zero(sa); zero(r); zero(f); zero(tmpsa);
}
