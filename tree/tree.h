#include <vector>
#include <iterator>
#include <algorithm>
#include <queue>

using namespace std;

class Tree {
public:
	class Iterator : public iterator<forward_iterator_tag, int> {
		public:
			Iterator(const Tree& _tree) : tree(_tree) {
				current = tree.root;
			}
			/*
			virtual Iterator& operator ++ () {
				return *this;
			}
			virtual Iterator& operator ++ (int) {
				return *this;
			}
			*/
			virtual Iterator& operator ++() = 0;
			int& operator * () {
				return current;
			}
		protected:
			int current;
			const Tree& tree;
	};

	class BFSIterator : public Iterator {
		public:
			BFSIterator(const Tree& _tree) : Iterator(_tree) {
				iterate();
			}

			BFSIterator operator ++ (int) {
				BFSIterator t = *this;
				++(*this);
				return t;
			}

			BFSIterator& operator ++ () {
				if(q.empty()) {
					current = -1;
				} else {
					current = q.front();
					q.pop();
					iterate();
				}

				return *this;
			}
		private:
			void iterate() {
				for(int i = 0; i < tree.childs[current].size(); ++i) {
					q.push(tree.childs[current][i]);
				}
			}
			queue<int> q;
	};

	class DFSIterator : public Iterator {
		public:
			DFSIterator(const Tree& _tree) : Iterator(_tree) {
				remaining = tree.parents.size();
				visited.resize(remaining, false);

				visited[current] = true;
				--remaining;
			}

			DFSIterator operator ++ (int) {
				DFSIterator t = *this;
				++(*this);
				return t;
			}

			DFSIterator& operator ++ () {
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
		private:
			int nextChild(int start) const {
				for(int i = 0; i < tree.childs[start].size(); ++i) {
					int next = tree.childs[start][i];
					if(!visited[next]) {
						return next;
					}
				}

				return -1;
			}
			vector<bool> visited;
			int remaining;
	};

	Tree() {}

	Tree(const Tree& _another) {
		parents = _another.parents;
		childs = _another.childs;
		root = _another.root;
	}

	void setRoot(int _root) {
		root = _root;
	}

	void addEdge(int _from, int _to) {
		int size = max(max(_from, _to), (int)childs.size()) + 1;
		childs.reserve(size+1); //LOLWUT???
		parents.reserve(size+1); //LOLWUT???
		childs.resize(size);
		parents.resize(size);

		childs[_from].push_back(_to);
		parents[_to] = _from;
	}

	DFSIterator getDFSIterator() {
		return DFSIterator(*this);
	}

	BFSIterator getBFSIterator() {
		return BFSIterator(*this);
	}
private:
	vector<int> parents;
	vector< vector<int> > childs;
	int root;
};


