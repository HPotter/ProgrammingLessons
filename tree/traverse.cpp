#include <iostream>
#include "tree.h"

using namespace std;

int main() {
	Tree t;
	t.setRoot(0);
	int edges;
	cin >> edges;
	for(int i = 0; i < edges; i++) {
		int x,y;
		cin >> x >> y;
		t.addEdge(x, y);
	}
	Tree::DFSIterator dfs = t.getDFSIterator();
	for(int i = 0; ; i++) {
		int t = *(dfs++);
		if(t < 0) break;
		cout << t;
	}
	cout << endl;
	Tree::BFSIterator bfs = t.getBFSIterator();
	for(int i = 0; ; i++) {
		int t = *(bfs++);
		if(t < 0) break;
		cout << t;
	}
	return 0;
}
