#pragma once
/*
Brady Hill
Dynamic Array Header File
Schoolwork for Full Sail University
*/

template <typename Type>

class DynArray
{
protected:
	Type * array;
	unsigned int Size, Capacity;

public:

	DynArray()
	{
		Size = 0; Capacity = 0;
		array = nullptr;
	}

	~DynArray()
	{
		delete[] array;
	}

	DynArray(const DynArray<Type>& that)
	{
		array = nullptr;
		*this = that;
	}

	DynArray<Type>& operator=(const DynArray<Type>& that)
	{
		if (this != &that)
		{
			delete[] array;
			Size = that.Size;
			Capacity = that.Capacity;
			array = new Type[that.Capacity];
			for (unsigned int i = 0; i < Size; i++)
			{
				array[i] = that.array[i];
			}
		}
		return *this;
	}

	Type& operator[](const unsigned int index)
	{
		return array[index];
	}

	const Type& operator[](const unsigned int index) const
	{
		return array[index];
	}

	unsigned int size() const
	{
		return Size;
	}

	unsigned int capacity() const
	{
		return Capacity;
	}

	void clear()
	{
		delete[] array;
		array = nullptr;
		Size = 0;
		Capacity = 0;
	}

	void append(const Type& item)
	{
		if (Capacity == 0)
		{
			Capacity = 1;
			array = new Type[Capacity];
			array[Size] = item;
			Size++;
		}
		else if (Size == Capacity && Capacity > 0)
		{
			Capacity *= 2;
			Type * temp = new Type[Capacity];
			for (unsigned int i = 0; i < Size; i++)
			{
				temp[i] = array[i];
			}
			delete[] array;
			array = temp;
			array[Size] = item;
			Size++;
		}
		else if (Size != Capacity)
		{
			array[Size] = item;
			Size++;
		}
	}

	void reserve(const unsigned int & newCap = 0)
	{
		if (newCap == 0 && Capacity == 0)
		{
			Capacity = 1;
			Type * temp = new Type[Capacity];
			for (unsigned int i = 0; i < Size; i++)
			{
				temp[i] = array[i];
			}
			delete[] array;
			array = temp;
		}
		else if (newCap > 0 && newCap > Capacity)
		{
			Capacity = newCap;
			Type * temp = new Type[Capacity];
			for (unsigned int i = 0; i < Size; i++)
			{
				temp[i] = array[i];
			}
			delete[] array;
			array = temp;
		}
		
		else if(newCap == 0 && Capacity > 0)
		{
			Capacity *= 2;
			Type * temp = new Type[Capacity];
			for (unsigned int i = 0; i < Size; i++)
			{
				temp[i] = array[i];
			}
			delete[] array;
			array = temp;
		}
		else if (newCap <= Capacity && Capacity > 1)
		{
		}
	}

};
