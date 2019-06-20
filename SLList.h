#pragma once

/*
Brady Hill
Schoolwork
Full Sail University
*/

// forward declaration
template<typename Type> class SLLIter;

// class SLList
template<typename Type> class SLList
{
	// the iterator is the list’s friend
	friend class SLLIter<Type>;

	// add members/methods here…
private:
	struct Node
	{
		Type element;

		Node *next;
	};
	Node *head;
	unsigned int Size;

public:

	SLList()
	{
		head = nullptr;
		Size = 0;
	}

	~SLList()
	{
		clear();
	}

	SLList<Type>& operator=(const SLList<Type>& that)
	{
		// check for self assignment
		// paranoia check
		if(this != &that)
		{
			// delete the old data
			clear();

			// if the right hand list is empty, do nothing
			if(that.head != nullptr)
			{
				// make a new head, and initialize it
				this->head = new Node;
				head->element = that.head->element;
				head->next = nullptr;

				// make a couple of iterator/ pointers
				Node* LHS = head;
				Node* RHS = that.head->next;

				// while the RHS list has another node
				while(RHS != nullptr)
				{
					// make a new node, connect and initialize
					LHS->next = new Node;
					LHS->next->element = RHS->element;
					LHS->next->next = nullptr;

					// update my pointers/iterators
					LHS = LHS->next;
					RHS = RHS->next;
				}
			}
			this->Size = that.Size;
		}

		// return the invoking object
		return *this;
	}

	SLList(const SLList<Type>& that)
	{	
		// make your pointers safe
		Size = 0;
		head = nullptr;

		// call the assignment operator
		*this = that;
	}

	void addHead(const Type& v)
	{
		Node * temp = new Node;
		temp->element = v;
		temp->next = head;
		head = temp;
		Size++;
	}

	void clear()
	{
		while(head != nullptr)
		{
			Node* temp = head;
			head = head->next;
			delete temp;
		}
		Size = 0;
	}

	void insert(SLLIter<Type>& index, const Type& v)
	{
		if(index.curr != nullptr)
		{
			// create a new ndoe, initialize it
			Node * temp = new Node;
			temp->element = v;
			temp->next = index.curr;

			if(nullptr == index.prev)
			{
				head = index.curr = temp;
			}
			else
			{
				index.prev->next = index.curr = temp;
			}

			++Size;
		}
	}

	void remove(SLLIter<Type>& index)
	{
		if(index.curr != nullptr)
		{
			Node* n = index.curr;
			// connect around the node
			if(index.curr == head)
				head = head->next;
			else
				index.prev->next = index.curr->next;
			// update the current
			index.curr = index.curr->next;
			// delete the node that we just disconnected
			delete n;
			--Size;
		}	
	}

	inline unsigned int size() const
	{
		return Size;
	}
};

// class SLLIter
template<typename Type> class SLLIter
{
	// the list is the iterator’s friend
	friend class SLList<Type>;

public:

	SLList<Type>* linkedList;

	typename SLList<Type>::Node *curr;
	typename SLList<Type>::Node *prev;

	SLLIter(SLList<Type>& listToIterate)
	{
		linkedList = &listToIterate;
		curr = linkedList->head;
		prev = nullptr;
	}

	void begin()
	{
		curr = linkedList->head;
		prev = nullptr;
	}

	bool end() const
	{
		return (curr == NULL);
	}

	SLLIter<Type>& operator++()
	{
		if(curr != nullptr)
		{
			this->prev = curr;
			this->curr = curr->next;
		}
		return *this;
	}

	Type& current() const
	{
		return curr->element;
	}
};

