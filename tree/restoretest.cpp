#include "restore.h"
#include <iostream>

void p_v(const vector<int>& t) {
	for(int i = 0; i < t.size(); i++) {
		cout << t[i] << " ";
	}
	cout << endl;
}

bool restoringTest(const vector<int>& bfs, const vector<int>& dfs) {
	Tree tree = buildTree(bfs, dfs);
	cout << tree;
	Tree::Iterator dfsIterator = tree.getDFSIterator();
	Tree::Iterator bfsIterator = tree.getBFSIterator();
	vector<int> bfsTraverse, dfsTraverse;
	while(true) {
		if(*dfsIterator < 0) break;
		bfsTraverse.push_back(*bfsIterator);
		dfsTraverse.push_back(*dfsIterator);
		dfsIterator++;
		bfsIterator++;
	}

	cout << "new bfs: ";
	p_v(bfsTraverse);
	cout << "new dfs: ";
	p_v(dfsTraverse);

	return (bfs == bfsTraverse) && (dfs == dfsTraverse);
}

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

	if(restoringTest(bfs, dfs)) {
		cout << "passed" << endl;
		return 0;
	} else {
		cout << "failed" << endl;
		return 1;
	}
}
