#include <iostream>
#include "graph.h"

using namespace std;

int main()
{
	graph g;

	cout << "Enter graph: ";
	cin >> g;
	cout << g << endl;

	cout << "is connected = " << g.is_connected() << endl;
	cout << "cc = " << g.cc() << endl;
	cout << "is acyclic " << g.is_acyclic() << endl;
    cout << "is bipartite " << g.is_bipartite() << endl;
    vector<int> p(g.n(), -1);
    cout << "distance between 0 and 1: " << g.distance(0, 1) << endl;
    cout << "distance between 2 and 1: " << g.distance(2, 1) << endl;
   // cout << "distance between 3 and 1: " << g.distance(3, 1) << endl;
   // cout << "distance between 0 and 3: " << g.distance(3, 0) << endl;
    cout << "girth " << g.girth() << endl;
}
