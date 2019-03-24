#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/* idea from following webpage
 * https://www.siggraph.org/education/materials/HyperGraph/video/mpeg/mpegfaq/huffman_tutorial.html
 */

struct huff {
	ll v; /* value */
	huff *r, *l; /* right, left branches */
};

typedef pair<ll, huff*> pih;

huff *build_huff(vector<ll> &e)
{
	priority_queue<pih, vector<pih>, greater<pih>> pq;
	for (auto &x: e)
		pq.push(make_pair(x, nullptr));

	while(pq.size() != 1) {
		/* Get 2 nodes with lower value */
		pih x = pq.top();
		pq.pop();
		pih y = pq.top();
		pq.pop();

		/* Combine them in a new node */
		huff *w = new huff;
		w->r = x.second;
		w->l= y.second;
		w->v = x.first+y.first;

		/* Push new one to the pq */
		pq.push(make_pair(w->v, w));
	}

	/* Only one node left => tree complete */
	return pq.top().second;
}

ll sum_nuke_huff(huff *x)
{
	/* Recursively sum all the values of the tree nodes while
	 * destroying the tree */
	if (!x)
		return 0;

	ll tot = x->v + sum_nuke_huff(x->r) + sum_nuke_huff(x->l);
	delete x->r;
	delete x->l;
	return tot;
}

int main()
{
	ll n;
	cin >> n;

	for (ll i = 0; i < n; i++) {
		ll t;
		cin >> t;
		vector<ll> a(t);
		for (ll j = 0; j < t; j++)
			cin >> a[j];

		huff *o = build_huff(a);
		cout << sum_nuke_huff(o) << endl;
		delete o;
	}
}
