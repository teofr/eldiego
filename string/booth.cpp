#include <vector>

using namespace std;

// Booth's lexicographically minimal string rotation algorithm
template<class U, class T>
int boothLCS(T &v) // O(n)
{
	size_t len = 2 * v.size();

	// Duplicate original data to avoid modular arithmetic
	vector<U> S(len);
	for (size_t i = 0, sz = v.size(); i < sz; i++)
		S[i] = S[v.size()+i] = v[i];

	// Failure function
	vector<int> f(len, -1);

	// Minimal rotation found so far
	int k = 0;

	for (size_t j = 1; j < S.size(); j++) {
		int i = f[j-k-1];
		while (i != -1 && S[j] != S[k+i+1]) {
			if (S[j] < S[k+i+1])
				k = j-i-1;
			i = f[i];
		}
		if (i == -1 && S[j] != S[k+i+1]) {
			if (S[j] < S[k+i+1])
				k = j;
			f[j-k] = -1;
		} else {
			f[j-k] = i+1;
		}
	}

	return k;
}
