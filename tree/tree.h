#include <vector>
#include <iterator>
#include <queue>
#include <iostream>

using namespace std;

class Tree {
public:
	class AbstractIterator : public iterator<forward_iterator_tag, int> {
		public:
			AbstractIterator(const Tree& _tree);
			AbstractIterator();
			const int& operator * () const;
		protected:
			int current;
			const Tree& tree;
	};

	class BFSIterator : public AbstractIterator {
		public:
			BFSIterator(const Tree& _tree);
			BFSIterator();
			virtual BFSIterator& operator ++ ();
			virtual BFSIterator operator ++ (int);
		private:
			void iterate();
			queue<int> q;
	};

	class DFSIterator : public AbstractIterator {
		public:
			DFSIterator(const Tree& _tree);
			DFSIterator();
			DFSIterator operator ++ (int);
			DFSIterator& operator ++ ();
		private:
			int nextChild(int start) const;
			vector<bool> visited;
			int remaining;
	};

	class Iterator {
		public:
			Iterator(const BFSIterator& _bfs);
			Iterator(const DFSIterator& _dfs);

			Iterator& operator ++ ();
			Iterator operator ++ (int);
			const int& operator * () const;
		private:
			bool isDFS;
			DFSIterator dfs;
			BFSIterator bfs;
			void prefixInc();
			void postfixInc();
			const int& unlink() const;
	};

	Tree();
	Tree(const Tree& _another);

	void setRoot(int _root);
	void addEdge(int _from, int _to);

	Iterator getDFSIterator() const;
	Iterator getBFSIterator() const;

	friend std::ostream& operator<< (std::ostream& result, const Tree& tree);
private:
	vector<int> parents;
	vector< vector<int> > childs;
	int root;
};


