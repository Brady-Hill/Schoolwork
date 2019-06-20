#pragma once
/*
Brady Hill
Schoolwork
Full Sail University
*/

template <typename Type> class BST
{
private:

	struct Node
	{
		Type element;
		Node* left;
		Node* right;

		Node(Type e, Node* r = nullptr, Node* l = nullptr)
		{
			element = e; right = r; left = l;
		}
	};

	Node* root;

	void inOrderPrint(Node* n) const
	{
		if (n != nullptr)
		{
			inOrderPrint(n->left);
			cout << n->element << ' ';
			inOrderPrint(n->right);
		}
	}

	void postClear(Node* n)
	{
		if (n != nullptr)
		{
			postClear(n->left);
			postClear(n->right);
			delete n;
		}
	}

	void preCopy(Node* n)
	{
		if (n != nullptr)
		{
			insert(n->element);
			preCopy(n->left);
			preCopy(n->right);
		}
	}

	void pCase0(Node* current, Node* parent)
	{
		//If current is the root...
		if (root == current)
			root = nullptr;
		//Else... (non root case)
		else
		{
			if (current == parent->left)
				parent->left = nullptr;
			// current must be equal to parent->right
			else
				parent->right = nullptr;
		}
		delete current;
	}
	
	void pCase1(Node* current, Node* parent)
	{
		if (current == root)
		{
			if (nullptr == current->left)
				root = current->right;
			else
				root = current->left;
		}
		else
		{
			if (parent->left == current)
			{
				if (nullptr == current->left)
					parent->left = current->right;
				else
					parent->left = current->left;
			}
			else
			{
				if (nullptr == current->left)
					parent->right = current->right;
				else
					parent->right = current->left;
			}
		}
		delete current;
	}

	bool pFindAndRemove(const Type& v)
	{
		if (nullptr == root)
			return false;
		Node* parent = nullptr;
		Node* current = root;

		while (current->element != v)
		{
			parent = current;
			if (current->element > v)
				current = current->left;
			else
				current = current->right;
			if (nullptr == current)
				return false;
		}
		//case 0
		if (nullptr == current->left && nullptr == current->right)
			pCase0(current, parent);

		//case 1
		else if (nullptr == current->left || nullptr == current->right)
			pCase1(current, parent);

		else
		{
			Node* minimum = current->right;
			Node* minParent = current;
			while (minimum->left != nullptr)
			{
				minParent = minimum;
				minimum = minimum->left;
			}
			current->element = minimum->element;

			if (nullptr == minimum->right)
				pCase0(minimum, minParent);
			else
				pCase1(minimum, minParent);
		}
	}

public:

	BST()
	{
		root = nullptr;
	}

	~BST()
	{
		clear();
	}

	BST& operator=(const BST& that)
	{
		if (this != &that)
		{
			clear();

			if (that.root != nullptr)
			{
				preCopy(that.root);
			}
		}
		return *this;
	}

	BST(const BST& that)
	{
		root = nullptr;

		*this = that;
	}

	void insert(const Type& v)
	{
		Node* n = new Node(v);
		Node* curr;
		if (root == nullptr)
		{
			root = n;
			curr = root;
		}
		else //if(root != nullptr)
		{
			curr = root;
			while (curr != nullptr)
			{
				if(n->element < curr->element)
				{
					if (curr->left == nullptr)
					{
						curr->left = n;
						return;
					}
					else
					{
						curr = curr->left;
					}
				}
				else
				{
					if (curr->right == nullptr)
					{
						curr->right = n;
						return;
					}
					else 
					{
						curr = curr->right;
					}
				}
			}
		}
	}

	bool findAndRemove(const Type& v)
	{
		return pFindAndRemove(v);
	}

	bool find(const Type& v) const
	{
		Node* curr = root;

		while (curr != nullptr)
		{
			if (v == curr->element)
				return true;
			else if (v < curr->element)
			{
				curr = curr->left;
			}
			else if (v >= curr->element)
			{
				curr = curr->right;
			}
		}
		return false;
	}

	void clear()
	{
		postClear(root);
		root = nullptr;
	}

	void printInOrder() const
	{
		inOrderPrint(root);
		cout << '\n';
	}
};