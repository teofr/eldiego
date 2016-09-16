#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
template <typename T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

int main(){
	ordered_set<int>  s;
	s.insert(1); 
	s.insert(3);
	cout << s.order_of_key(3) << endl; // s.order_of_key(x): number of elements in s strictly less than x.
	cout << *s.find_by_order(0) << endl; // s.find_by_order(i): i-th smallest number in s. (empieza en 0)
	cout << *s.lower_bound(1) << endl;
}
//order_of_key(k): devuelve la pos del lower bound de k
//find_by_order(i) devuelve iterador al i-esimo elemento
//Ej: 12, 100, 505, 1000, 10000.
//order_of_key(10) == 0, order_of_key(100) == 1,
//order_of_key(707) == 3, order_of_key(9999999) == 5

/*
Si son int se puede hacer con un rmq y busqueda binaria.

rmq[i] = 1 si i esta 
rmq[i] = 0 si i no esta

rmq.get(i,j) = suma en el intervalo [i,j)

order_of_key(i) == rmq.get(0,i)
find_by_order(o) == busqueda binaria en i / rmq.get(0,i+1) == o
lower_bound(i) == find_by_order(order_of_key(i)-1)
*/
