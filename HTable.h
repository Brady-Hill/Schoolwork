#pragma once
#include "SLList.h"
/*
Brady Hill
Schoolwork
Full Sail University
*/

template <typename Type> class HTable
{
public:
	Type(*pf) (const Type& a);
	SLList<Type> *hashList;
	unsigned int bucketnum;

	HTable(unsigned int numOfBuckets, unsigned int(*hFunction) (const Type &v))
	{
		pf = hFunction;
		bucketnum = numOfBuckets;
		hashList = new SLList<Type>[numOfBuckets];
	}

	~HTable()
	{
		delete[] hashList;
	}

	HTable<Type>& operator=(const HTable<Type>& that)
	{
		//paranoia check
		if (this != &that)
		{
			//delete old memory
			delete[] hashList;

			//make new memory
			bucketnum = that.bucketnum;
			hashList = new SLList<Type>[bucketnum];

			//copy some data
			for (unsigned int i = 0; i < bucketnum; ++i)
			{
				hashList[i] = that.hashList[i];
			}
			pf = that.pf;
		}
		return *this;
	}

	HTable(const HTable<Type>& that)
	{
		//initialize pointers that will have "New" called on them
		hashList = nullptr;

		*this = that;
	}

	void insert(const Type& v)
	{
		hashList[pf(v)].addHead(v);
	}

	bool findAndRemove(const Type& v)
	{
		unsigned int hash = pf(v);
		SLLIter<Type> iter(hashList[hash]);
		for (iter.begin(); !iter.end(); ++iter)
		{
			if (iter.current() == v)
			{
				hashList[hash].remove(iter);
				return true;
			}
		}
		return false;
	}

	void clear()
	{
		for (unsigned int i = 0; i < bucketnum; i++)
		{
			hashList[i].clear();
		}
	}

	int find(const Type& v) const
	{
		unsigned int hash = pf(v);
		SLLIter<Type> iter(hashList[hash]);
		for (iter.begin(); !iter.end(); ++iter)
		{
			if (iter.current() == v)
			{
				return hash;
			}
		}
		return -1;
	}
};