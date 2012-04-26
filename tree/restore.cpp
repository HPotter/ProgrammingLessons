#include <iostream>
#include "tree.h"

using namespace std;

void p_v(const vector<int>& t) {
	for(int i = 0; i < t.size(); i++) {
		cout << t[i] << " ";
	}
	cout << endl;
}


vector<int> subsequence(const vector<int>& where, const vector<int>& what) {
	vector<int> result;
	result.reserve(what.size());

	for(vector<int>::const_iterator it = where.begin(); it != where.end(); ++it) {
		if(find(what.begin(), what.end(), *it) != what.end()) {
			result.push_back(*it);
		}
	}

	return result;
}

vector<int> newLayer(const vector<int>& bfs, const vector<int>& dfs) {
	int i = 1;
	while( (i + 1 < bfs.size()) && (bfs[i] == dfs[i]) && (bfs[i+1] == dfs[i+1]) ) {
		++i;
	}
	++i;

	//Now dfs[i] is the first vortex with d == 2
	vector<int> layer(bfs.begin() + 1, find(bfs.begin(), bfs.end(), dfs[i]));

	return layer;
}

vector< vector<int>::const_iterator > newLayerIterators(const vector<int>& bfs, const vector<int>& dfs) {
	vector<int> layer = newLayer(bfs, dfs);
	vector< vector<int>::const_iterator > layerIterators;
	for(int i = 0; i < layer.size(); ++i) {
		layerIterators.push_back(find(dfs.begin(), dfs.end(), layer[i]));
	}
	layerIterators.push_back(dfs.end());
	return layerIterators;

}


void buildTree(const vector<int>& bfs, const vector<int>& dfs, Tree& tree, int root) {
//	int root = bfs[0];

	if(bfs.size() == 2) {
		cout << "newEdge (" << root << ", " << bfs[1] << ")" << endl;
		tree.addEdge(root, bfs[1]);
	} else if(bfs.size() > 2) {
		vector< vector<int>::const_iterator > layerIterators = newLayerIterators(bfs, dfs);
		for(int i = 0; i < layerIterators.size() - 1; ++i) {
			cout << "newEdge (" << bfs[0] << ", " << *layerIterators[i] << ")" << endl;
			tree.addEdge(bfs[0], *layerIterators[i]);

			vector<int> newDfs(layerIterators[i], layerIterators[i+1]);
			vector<int> newBfs = subsequence(bfs, newDfs);

			buildTree(newBfs, newDfs, tree, bfs[0]);
		}
	}
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

//	p_v(t);
	Tree tree;
	tree.setRoot(bfs[0]);
	buildTree(bfs, dfs, tree, bfs[0]);

	return 0;
}
