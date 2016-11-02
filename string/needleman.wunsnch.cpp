/* Longest common subsequence: DEL=INS=0, MATCH=1, MISMATCH=-INF
 * Hamming: DEL=INS=-INF, MATCH=0, MISMATCH=1
 * String alignment: normalmente DEL=INS=-1, MATCH=+2, MISMATCH=-1 */
#define DEL (0)
#define INS (0)
#define MATCH (1)
#define MISMATCH (-10000000)
#define MAXLEN 10000
ll nwt[MAXLEN][MAXLEN];

ll needleman_wunsnch(const char *A, const char *B) {
	ll n = strlen(A), m = strlen(B);

	forn(i, n+1) nwt[i][0] = i * INS;
	forn(j, m+1) nwt[0][j] = j * DEL;

	forr(i, 1, n+1) forr(j, 1, m+1) {
		nwt[i][j] = nwt[i-1][j-1] + (A[i-1] == B[j-1] ? MATCH : MISMATCH);
		nwt[i][j] = max(nwt[i][j], nwt[i - 1][j] + DEL);
		nwt[i][j] = max(nwt[i][j], nwt[i][j - 1] + INS);
	}

	return nwt[n][m];
}

string lcs_construct(const char *A, const char *B) {
	ll len = needleman_wunsnch(A, B), i = strlen(A), j = strlen(B);
	string s;
	s.resize(len);

	while (i > 0 && j > 0) {
		if (nwt[i-1][j] == nwt[i][j]) --i;
		else if (nwt[i][j-1] == nwt[i][j]) --j;
		else {
			s[--len] = A[i-1];
			--i, --j;
		}
	}

	return s;
}
