#include <vector>
#include <iterator>
#include <algorithm>
#include <queue>
#include <iostream>

using namespace std;

class Tree {
public:
	class AbstractIterator : public iterator<forward_iterator_tag, int> {
		public:
			AbstractIterator(const Tree& _tree) : tree(_tree) {
				current = tree.root;
			}

			AbstractIterator() : tree(Tree()) {}
			
			virtual AbstractIterator& operator ++ () {
				return *this;
			}
			/*
			virtual AbstractIterator& operator ++ (int) {
				return *this;
			}
			*/
//			virtual AbstractIterator& operator ++() = 0;
//			virtual AbstractIterator operator ++(int) = 0;
			int& operator * () {
				return current;
			}
		protected:
			int current;
			const Tree& tree;
	};

	class BFSIterator : public AbstractIterator {
		public:
			BFSIterator(const Tree& _tree) : AbstractIterator(_tree) {
				iterate();
			}

			BFSIterator() {}

			virtual BFSIterator operator ++ (int) {
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

	class DFSIterator : public AbstractIterator {
		public:
			DFSIterator(const Tree& _tree) : AbstractIterator(_tree) {
				remaining = tree.parents.size();
				visited.resize(remaining, false);

				visited[current] = true;
				--remaining;
			}

			DFSIterator() {}

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

	class Iterator {
		public:
			Iterator(const BFSIterator& _bfs) : bfs(_bfs), isDFS(false) {}
			Iterator(const DFSIterator& _dfs) : dfs(_dfs), isDFS(true) {}

			Iterator& operator ++ () {
				prefixInc();
				return *this;
			}
			Iterator operator ++ (int) {
				Iterator t = *this;
				postfixInc();
				return t;
			}
			int& operator * () {
				return unlink();
			}
		private:
			bool isDFS;
			DFSIterator dfs;
			BFSIterator bfs;
			void prefixInc() {
				if(isDFS) {
					++dfs;
				} else {
					++bfs;
				}
			};
			void postfixInc() {
				if(isDFS) {
					dfs++;
				} else {
					bfs++;
				}
			};
			int& unlink() {
				if(isDFS) {
					return *dfs;
				} else {
					return *bfs;
				}
			}
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
//		cout << "newEdge (" << _from << ", " << _to << ")" << endl;
		int size = max(max(_from, _to) + 1, (int)childs.size());
		childs.reserve(size); //LOLWUT???
		parents.reserve(size); //LOLWUT???
		childs.resize(size);
		parents.resize(size);

		childs[_from].push_back(_to);
		parents[_to] = _from;
	}

	Iterator getDFSIterator() {
		return Iterator(DFSIterator(*this));
	}

	Iterator getBFSIterator() {
		return Iterator(BFSIterator(*this));
	}

	void print() const {
		cout << "root " << root << endl;
		for(int i = 0; i < childs.size(); i++) {
			cout << i << "childs:";
			for(int j = 0; j < childs[i].size(); j++) {
				cout << " " << childs[i][j];
			}
			cout << endl;
		}
	}

private:
	vector<int> parents;
	vector< vector<int> > childs;
	int root;
};


