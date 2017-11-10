#include <bits/stdc++.h>
using namespace std;
#define forsn(i,s,n) for(tint i = (tint)(s); i < (tint)(n); i++)
#define forn(i, n) forsn(i,0,n)
#define dforsn(i,s,n) for(tint i = (tint)(n); i >= (tint)(s); i--)
#define dforn(i,n) dforsn(i,0,n)
#define pb push_back
#define mp make_pair
#define fst first
#define snd second
typedef long long tint;

#ifdef DEBUG
#define debug(v) cerr << #v << ": " << v << endl;
#else
#define debug(v)
#endif



#define fpos adla

/* Suffix tree sacado de aca
	http://codeforces.com/blog/entry/16780
    No es tan rapido como Ukkonen pero es mas sencillo
*/
#include <bits/stdc++.h>

using namespace std;
tint res;

struct suffT{
    int inf;
    int maxn;
    string orig;
    string s;
    vector<map<int, int> > to;
    vector<int> len, fpos, link;
    int node, pos, sz, n;

    suffT(string k){
        inf = 1000000000;
        orig = k;
        orig += '#'; //Caracter que no aparezca
        s = orig;
        maxn = 4*s.size() + 3;
        to = vector<map<int, int> > (maxn);
        len = vector<int> (maxn, 0);
        fpos = vector<int> (maxn, 0);
        link = vector<int> (maxn, 0);
        node = pos = n = 0;
        len[0] = 1e9;
        sz = 1;

        for(int i = 0; i < s.size(); i++){
            debug(i);
            add_letter(s[i]);
        }
    }

    int make_node(int _pos, int _len){
        fpos[sz] = _pos;
        len [sz] = _len;
        return sz++;
    }

    void go_edge(){
        while(pos > len[to[node][s[n - pos]]]){
            node = to[node][s[n - pos]];
            pos -= len[node];
        }
    }

    void add_letter(int c){
        s[n++] = c;
        pos++;
        int last = 0;
        while(pos > 0){
            go_edge();
            int edge = s[n - pos];
            int &v = to[node][edge];
            int t = s[fpos[v] + pos - 1];
            if(v == 0){
                v = make_node(n - pos, inf);
                link[last] = node;
                last = 0;
            }else if(t == c){
                link[last] = node;
                return;
            }else{
                int u = make_node(fpos[v], pos - 1);
                to[u][c] = make_node(n - 1, inf);
                to[u][t] = v;
                fpos[v] += pos - 1;
                len [v] -= pos - 1;
                v = u;
                link[last] = u;
                last = u;
            }
            if(node == 0)
                pos--;
            else
                node = link[node];
        }
    }


    int search(string k){
    	int cur = 0;
    	bool encontrado = true;
    	int visto = 0;
    	while (encontrado and visto < k.size()){
    		if (encontrado = encontrado and to[cur].find(k[visto]) != to[cur].end()){
    			cur = to[cur][k[visto]];
    			forsn(i, fpos[cur], len[cur] + fpos[cur]){
    				if (visto == k.size()) return true;
    				if (k[visto++] != s[i]) return false;
    			}
    		}
    	}
    	return false;
    }

    pair<int, int> dfs(int cur = 0, int acum = 0){
        if (len[cur] > maxn and cur != 0){
            pair<int, int> resp {1, 0};
            return resp;
        }

    	int hojas = 0;
        int contados = 0;
    	bool todosHojas = true;
    	for(const auto&  n : to[cur]){
    		pair<int, int> next = dfs(n.snd, (len[n.snd] > maxn ? s.size() - 1 : acum + len[n.snd]));//o len[n.snd]
    		todosHojas = todosHojas && (next.fst == 1);
    		hojas += next.fst;
            contados += next.snd;
    	}
    	if (hojas > 1 and todosHojas){
    		res += (tint)acum;
            contados++;
    	}else if (contados > 1){
            res -= (tint)((contados - 1)*acum);
            contados = 1;
        }
    	return make_pair(hojas, contados);
    }

};

/*


#define fpos adla
const int inf = 1e9;
const int maxn = 202345;
char s[maxn]; // El string
map<int, int> to[maxn];
int len[maxn], fpos[maxn], link[maxn];
int node, pos;
int sz = 1, n = 0;


void init(){

    forn(i, maxn){
        to[i].clear();
        //len[i] = fpos[i] = link[i] = 0;

    }
    node = pos = 0;
    sz = 1;
    n = 0;
    len[0] = inf;
}

int make_node(int _pos, int _len)
{
    fpos[sz] = _pos;
    len [sz] = _len;
    return sz++;
}

void go_edge()
{
    while(pos > len[to[node][s[n - pos]]])
    {
        node = to[node][s[n - pos]];
        pos -= len[node];
    }
}

void add_letter(int c)
{
    debug(c);
    s[n++] = c;
    pos++;
    int last = 0;
    while(pos > 0)
    {
        go_edge();
        int edge = s[n - pos];
        int &v = to[node][edge];
        int t = s[fpos[v] + pos - 1];
        if(v == 0)
        {
            v = make_node(n - pos, inf);
            link[last] = node;
            last = 0;
        }
        else if(t == c)
        {
            link[last] = node;
            return;
        }
        else
        {
            int u = make_node(fpos[v], pos - 1);
            to[u][c] = make_node(n - 1, inf);
            to[u][t] = v;
            fpos[v] += pos - 1;
            len [v] -= pos - 1;
            v = u;
            link[last] = u;
            last = u;
        }
        if(node == 0)
            pos--;
        else
            node = link[node];
    }
}

*/




int main() {
	ios::sync_with_stdio(0); cin.tie(0);
	//string disk;
    string ss;
	while (cin >> ss){
		if (ss == "*") break;

        suffT st (ss);

		res = 0;

		st.dfs();
        /*
        forn(i, 25){
    		debug(i);
            debug(to[i]['m']);
            debug(to[i]['i']);
            debug(to[i]['s']);
            debug(to[i]['p']);
    		debug(to[i]['#']);
    		debug(len[i]);
    		debug(fpos[i]);

    	}
        */

		cout << res << endl;


	}


	return 0;
}
