#include "restore.h"

using namespace std;

vector<int> trim(const vector<int> _input) {
	vector<int>::const_iterator it = _input.begin();
	for(; *it == DIVIDER; ++it) {}

	vector<int> result(it, _input.end());
	while(result.back() == DIVIDER) {
		result.pop_back();
	}

	return result;
}

vector<int> subsequence(const vector<int>& where, const vector<int>& what) {
	vector<int> result;
	result.reserve(where.size());

	for(int i = 0; i < where.size(); i++) {
		if(std::find<vector<int>::const_iterator, int>(what.begin(), what.end(), where[i]) != what.end()) {
			result.push_back(where[i]);
		} else {
			if( !(result.empty()) && (result.back() != DIVIDER) ) {
				result.push_back(DIVIDER);
			}
		}
	}

	while(result.back() == DIVIDER) {
		result.pop_back();
	}

	return result;
}

vector<int> newLayer(const vector<int>& bfs, const vector<int>& dfs) {
	int i = 1;
	while(bfs[i] == DIVIDER) {
		i++;
	}
	while( (i + 1 < bfs.size()) && (bfs[i] == dfs[i]) && (bfs[i+1] == dfs[i+1]) ) {
		++i;
	}
	++i;

	//Now dfs[i] is the first vortex with d == 2

	//let's find DIVIDER or dfs[i] in bfs
	int j = 2;
	for(; bfs[j] != DIVIDER && bfs[j] != dfs[i] && j < bfs.size(); j++) {}

	vector<int> layer(bfs.begin() + 1, bfs.begin() + j);

	return trim(layer);
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
	if(bfs.size() == 2) {
		tree.addEdge(root, bfs[1]);
	} else if(bfs.size() > 2) {
		vector< vector<int>::const_iterator > layerIterators = newLayerIterators(bfs, dfs);
		for(int i = 0; i < layerIterators.size() - 1; ++i) {
			tree.addEdge(bfs[0], *layerIterators[i]);

			vector<int> newDfs(layerIterators[i], layerIterators[i+1]);
			vector<int> newBfs = subsequence(bfs, newDfs);

			buildTree(newBfs, newDfs, tree, newBfs[0]);
		}
	}
}

Tree buildTree(const vector<int>& bfs, const vector<int>& dfs) {
	Tree tree;
	tree.setRoot(bfs[0]);
	buildTree(bfs, dfs, tree, bfs[0]);
	return tree;
}


