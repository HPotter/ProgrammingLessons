#include "tree.h"

//Tree::AbstractIterator
Tree::AbstractIterator::AbstractIterator(const Tree& _tree) : tree(_tree) {
	current = tree.root;
}

Tree::AbstractIterator::AbstractIterator() : tree(Tree()) {}

const int& Tree::AbstractIterator::operator * () const {
	return current;
}

//Tree::AbstractIterator::BFSIterator
//public
Tree::BFSIterator::BFSIterator(const Tree& _tree) : Tree::AbstractIterator(_tree) {
	iterate();
}

Tree::BFSIterator::BFSIterator() {}

Tree::BFSIterator Tree::BFSIterator::operator ++ (int) {
	Tree::BFSIterator t = *this;
	++(*this);
	return t;
}

Tree::BFSIterator& Tree::BFSIterator::operator ++ () {
	if(q.empty()) {
		current = -1;
	} else {
		current = q.front();
		q.pop();
		iterate();
	}

	return *this;
}

//private
void Tree::BFSIterator::iterate() {
	for(int i = 0; i < tree.childs[current].size(); ++i) {
		q.push(tree.childs[current][i]);
	}
}

//Tree::DFSIterator
//public
Tree::DFSIterator::DFSIterator(const Tree& _tree) : Tree::AbstractIterator(_tree) {
	remaining = tree.parents.size();
	visited.resize(remaining, false);

	visited[current] = true;
	--remaining;
}

Tree::DFSIterator::DFSIterator() {}

Tree::DFSIterator Tree::DFSIterator::operator ++ (int) {
	Tree::DFSIterator t = *this;
	++(*this);
	return t;
}

Tree::DFSIterator& Tree::DFSIterator::operator ++ () {
	if(remaining == 0) {
		current = -1;
	} else {
		int next;
		while( (next = nextChild(current)) == -1) {
			current = tree.parents[current];
		}

		current = next;
		visited[current] = true;
		--remaining;
	}

	return *this;
}

//private
int Tree::DFSIterator::nextChild(int start) const {
	for(int i = 0; i < tree.childs[start].size(); ++i) {
		int next = tree.childs[start][i];
		if(!visited[next]) {
			return next;
		}
	}

	return -1;
}

//Tree::Iterator
Tree::Iterator::Iterator(const Tree::BFSIterator& _bfs) : bfs(_bfs), isDFS(false) {}
Tree::Iterator::Iterator(const Tree::DFSIterator& _dfs) : dfs(_dfs), isDFS(true) {}

Tree::Iterator& Tree::Iterator::operator ++ () {
	prefixInc();
	return *this;
}

Tree::Iterator Tree::Iterator::operator ++ (int) {
	Tree::Iterator t = *this;
	postfixInc();
	return t;
}

const int& Tree::Iterator::operator * () const {
	return unlink();
}

//private
void Tree::Iterator::prefixInc() {
	if(isDFS) {
		++dfs;
	} else {
		++bfs;
	}
}

void Tree::Iterator::postfixInc() {
	if(isDFS) {
		dfs++;
	} else {
		bfs++;
	}
}

const int& Tree::Iterator::unlink() const {
	if(isDFS) {
		return *dfs;
	} else {
		return *bfs;
	}
}

//Tree
//public
Tree::Tree() {}

Tree::Tree(const Tree& _another) {
	parents = _another.parents;
	childs = _another.childs;
	root = _another.root;
}

void Tree::setRoot(int _root) {
	root = _root;
}

void Tree::addEdge(int _from, int _to) {
	int size = max(max(_from, _to) + 1, (int)childs.size());
	childs.reserve(size); //LOLWUT???
	parents.reserve(size); //LOLWUT???
	childs.resize(size);
	parents.resize(size);

	childs[_from].push_back(_to);
	parents[_to] = _from;
}

Tree::Iterator Tree::getDFSIterator() const {
	return Tree::Iterator(Tree::DFSIterator(*this));
}

Tree::Iterator Tree::getBFSIterator() const {
	return Tree::Iterator(Tree::BFSIterator(*this));
}

//output
std::ostream& operator<< (std::ostream& result, const Tree& tree) {

	result << "root " << tree.root << std::endl;
	for(int i = 0; i < tree.childs.size(); i++) {
		result << i << "childs:";
		for(int j = 0; j < tree.childs[i].size(); j++) {
			result << " " << tree.childs[i][j];
		}
		result << std::endl;
	}

	return result;
}
