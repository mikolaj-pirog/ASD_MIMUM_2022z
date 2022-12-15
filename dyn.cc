// https://github.com/Bibeknam/algorithmtutorprograms/blob/master/data-structures/splay-trees/SplayTree.cpp
// Splay tree implementation in C++
// Author: Algorithm Tutor
// Tutorial URL: http://algorithmtutor.com/Data-Structures/Tree/Splay-Trees/

#include <iostream>

using namespace std;

// data structure that represents a node in the tree
struct Node {
	int krotonsc, wartosc, rozmiarLewego, rozmiarPrawego;// holds the key
	Node *parent;                                        // pointer to the parent
	Node *left;                                          // pointer to left child
	Node *right;                                         // pointer to right child

	Node(int krotonsc, int wartosc, Node *parent) {
		this->krotonsc = krotonsc;
		this->wartosc = wartosc;
		this->parent = parent;
		left = nullptr;
		right = nullptr;
		rozmiarLewego = 0;
		rozmiarPrawego = 0;
	}
};

typedef Node *NodePtr;

// class SplayTree implements the operations in Splay tree
class SplayTree {
private:
	NodePtr root;


	NodePtr searchTreeHelper(NodePtr node, int j) {
		if (node == nullptr || (j >= node->rozmiarLewego && j <= node->rozmiarLewego + node->krotonsc)) {
			return node;
		}

		if (j < node->rozmiarLewego) {
			return searchTreeHelper(node->left, j);
		}
		return searchTreeHelper(node->right, j - node->rozmiarLewego - node->krotonsc);
	}

	void printHelper(NodePtr root, string indent, bool last) {
		// print the tree structure on the screen
		if (root != nullptr) {
			cout << indent;
			if (last) {
				cout << "└────";
				indent += "     ";
			} else {
				cout << "├────";
				indent += "|    ";
			}

			cout << root->wartosc << ": kro:" << root->krotonsc << endl;

			printHelper(root->left, indent, false);
			printHelper(root->right, indent, true);
		}
	}

	// rotate left at node x
	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	// rotate right at node x
	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	// splaying
	void splay(NodePtr x) {
		while (x->parent) {
			if (!x->parent->parent) {
				if (x == x->parent->left) {
					// zig rotation
					rightRotate(x->parent);
				} else {
					// zag rotation
					leftRotate(x->parent);
				}
			} else if (x == x->parent->left && x->parent == x->parent->parent->left) {
				// zig-zig rotation
				rightRotate(x->parent->parent);
				rightRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->right) {
				// zag-zag rotation
				leftRotate(x->parent->parent);
				leftRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->left) {
				// zig-zag rotation
				leftRotate(x->parent);
				rightRotate(x->parent);
			} else {
				// zag-zig rotation
				rightRotate(x->parent);
				leftRotate(x->parent);
			}
		}
	}

public:
	SplayTree() {
		root = nullptr;
	}

	// search the tree for the key k
	// and return the corresponding node
	NodePtr searchTree(int k) {
		NodePtr x = searchTreeHelper(this->root, k);
		if (x) {
			//splay(x);
		}
		return x;
	}

	// insert the key to the tree in its appropriate position
	void insert(int j, int x, int k) {
		NodePtr parent = nullptr;
		NodePtr placeToInsert = this->root;

		while (placeToInsert != nullptr) {
			parent = placeToInsert;
			if (placeToInsert->rozmiarLewego <= j && j <= placeToInsert->rozmiarLewego + placeToInsert->krotonsc) {
				if (placeToInsert->wartosc == x) {
					placeToInsert->krotonsc += k;
					return;
				} else {
					Node *to_insert = new Node(k, x, placeToInsert->parent);
					placeToInsert->parent = placeToInsert;
					if (to_insert->parent != nullptr && to_insert->parent->left == placeToInsert)
						to_insert->parent->left = to_insert;
					else if (to_insert->parent != nullptr)
						to_insert->parent->right = to_insert;
					else
						root = to_insert;

					Node *left_half = new Node(j - placeToInsert->rozmiarLewego, placeToInsert->wartosc, to_insert);
					Node *right_half = new Node(placeToInsert->krotonsc - left_half->krotonsc, placeToInsert->wartosc, to_insert);
					to_insert->left = left_half;
					to_insert->right = right_half;

					left_half->left = placeToInsert->left;
					left_half->rozmiarLewego = placeToInsert->rozmiarLewego;
					left_half->right = nullptr;

					right_half->right = placeToInsert->right;
					right_half->rozmiarPrawego = placeToInsert->rozmiarPrawego;
					right_half->left = nullptr;

					to_insert->rozmiarLewego += left_half->krotonsc;
					to_insert->rozmiarPrawego += right_half->krotonsc;
				}
			}

			if (placeToInsert->rozmiarLewego > j) {
				placeToInsert = placeToInsert->left;
			} else {
				j -= (placeToInsert->rozmiarLewego + placeToInsert->krotonsc);
				placeToInsert = placeToInsert->right;
			}
		}

		// y is parent of x
		//placeToInsert->parent = parent;
		if (parent == nullptr) {
			root = new Node(k, x, nullptr);
		} else if (parent->rozmiarLewego > j) {
			parent->left = new Node(k, x, parent);
			parent->rozmiarLewego += k;
			//(parent->left);
		} else {
			parent->right = new Node(k, x, parent);
			parent->right += k;
			//splay(parent->right);
		}

		// splay the node
		//splay(node);
	}

	NodePtr getRoot() {
		return this->root;
	}

	// print the tree structure on the screen
	void prettyPrint() {
		printHelper(this->root, "", true);
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	auto *root = new SplayTree();
	int m;
	cin >> m;
	for (int i = 0; i < m; i++) {
		char t;
		cin >> t;
		if (t == 'i') {
			int j, x, k;
			cin >> j >> x >> k;
			cout << j << "|" << x << "|" << k << "|";
			root->insert(j, x, k);
		} else {
			int j;
			cin >> j;
			cout << j << "|";
			auto res = root->searchTree(j);
			if (res == nullptr)
				cout << "eee";
			else
				cout << res->wartosc << "\n";
		}
	}

	return 0;
}
