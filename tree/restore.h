#include "tree.h"
#include <algorithm>

using namespace std;

const int DIVIDER = -1;

vector<int> trim(const vector<int> _input);

vector<int> subsequence(const vector<int>& where, const vector<int>& what);

vector<int> newLayer(const vector<int>& bfs, const vector<int>& dfs);

vector< vector<int>::const_iterator > newLayerIterators(const vector<int>& bfs, const vector<int>& dfs);

void buildTree(const vector<int>& bfs, const vector<int>& dfs, Tree& tree, int root);

Tree buildTree(const vector<int>& bfs, const vector<int>& dfs);
