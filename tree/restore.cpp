#include <iostream>
#include "restore.h"

int main() {
	int n;
	cin >> n;
	vector<int> dfs(n, 0), bfs(n, 0);
	for(int i = 0; i < n; ++i) {
		cin >> bfs[i];
	}
	for(int i = 0; i < n; ++i) {
		cin >> dfs[i];
	}

	Tree tree;
	buildTree(bfs, dfs, tree);

	return 0;
}
