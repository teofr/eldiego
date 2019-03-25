//codeforces.com/blog/entry/8219

convex hull trick 1: dp[i] = min{dp[j] + b[j] * a[i]}, j < i. Si se cumple b[j] >= b[j+1] y a[i] <= a[i+1] entonces pasa de O(n^2) a O(n) sino pasa a O(nlogn)

input N
for i in [0..N)
     input a[i]
     input b[i]
let E = empty lower envelope structure
let dp[0] = 0
add the line y=mx+b to E, where m=b[0] and b=dp[0] //b is zero
for i in [1..N)
     dp[i] = E.query(a[i])
     if i<N
          E.add(m=b[i],b=dp[i])
print dp[N]

convex hull trick 2: dp[i][j] = min{dp[i-1][k] + b[k] * a[j]}, k < j. Si se cumple b[k] >= b[k+1] y a[j] <= a[j+1] entonces pasa de O(kn^2) a O(kn) sino pasa O(knlogn)

divide and conquer: dp[i][j] = min{dp[i-1][k] + C[k (o k+1?) ][j]}, k < j. Se debe cumplir: A[i][j] <= A[i][j+1]. Pasa de O(kn^2) a O(knlogn)
Donde A[i][j] es el minimo k tal que dp[i][j] = dp[i-1][k] + C[k][j]
Tambien es aplicable si:
C[a][c] + C[b][d] <= C[a][d] + C[b][c] y C[b][c] <= C[a][d], a<=b<=c<=d

def ComputeDP(i, jleft, jright, kleft, kright):
  # Select the middle point
  jmid = (jleft + jright) / 2
  # Compute the value of dp[i][jmid] by definition of DP
  dp[i][jmid] = +INFINITY
  bestk = -1
  for k in range[kleft, jmid):
	if dp[i - 1][k] + C[k + 1][jmid] < best:
	  dp[i][jmid] = dp[i - 1][k] + C[k + 1][jmid]
	  bestk = k
  # Divide and conquer
  if jleft < jmid:
	ComputeDP(i, jleft, jmid, kleft, bestk)
  if jmid + 1 < jright:
	ComputeDP(i, jmid + 1, jright, bestk, kright)

def ComputeFullDP:
  Initialize dp for i = 0 somehow
  for i in range(1, m):
	ComputeDP(i, 0, n, 0, n)

knuth: dp[i][j] = min(dp[i][k] + dp[k][j]) + C[i][j], i < k < j.
Se debe cumplir: A[i, j - 1] <= A [i, j] <= A[i + 1, j].
Pasa de O(n^3) a O(n^2)
Donde A[i][j] es el minimo k tal que dp[i][j] = dp[i][k] + dp[k][j] + C[i][j]
Tambien es aplicable si:
C[a][c] + C[b][d] <= C[a][d] + C[b][c] y C[b][c] <= C[a][d], a<=b<=c<=d

for (int s = 0; s<=k; s++)
	for (int l = 0; l+s<=k; l++) {              //l - left point
	  int r = l + s;                            //r - right point
	  if (s < 2) {
		res[l][r] = 0;                          //DP base - nothing to break
		A[l][r] = l;                          //A is equal to left border
		continue;
	  }
	  int aleft = A[l][r-1];                  //Knuth's trick: getting bounds on m
	  int aright = A[l+1][r];
	  res[l][r] = INF;
	  for (int a = max(l+1,aleft); a<=min(r-1,aright); a++) {     //iterating for a in the bounds only
		int act = res[l][a] + res[a][r] + (C[l][r]);
		if (res[l][r] > act) {                 //relax current solution
		  res[l][r] = act;
		  A[l][r] = a;
		}
	  }
	}
