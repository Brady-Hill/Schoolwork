#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "DynArray.h"
#include "SLList.h"
using namespace std;

/*
Brady Hill
Schoolwork
Full Sail University
*/

#define SORTSTORE 1
#define SEARCHSTORE 2
#define BUYITEM 3
#define SELLITEM 4
#define UNDOTRANSACTION 5
#define TYPE 1
#define NAME 2
#define COST 3
#define WEIGHT 4

string convertToLower(string a)
{
	for (unsigned int i = 0; i < a.length(); i++)
	{
		a[i] = tolower(a[i]);
	}
	return a;
}
struct Item
{
	string type;
	string name;
	unsigned int cost;
	unsigned int weight;
};
struct Transaction
{
	Item theItem;
	bool bought;
};

DynArray<Item> contents;
SLList <Item> items;
SLList<Transaction> theHistory;
int coins = 5000, weight = 0, maxWeight = 50;

class TransactionManager
{
public:
	void Buy()
	{
		Transaction t;
		SLLIter<Item> tmp(items);
		tmp.begin();
		t.theItem = tmp.curr->element;
		t.bought = true;
		theHistory.addHead(t);
	}
	void Sell(Item a)
	{
		Transaction t;
		t.theItem = a;
		t.bought = false;
		theHistory.addHead(t);

	}
	void Undo()
	{
		SLLIter<Transaction> tmp(theHistory);
		SLLIter<Item> tmp2(items);
		tmp.begin();
		tmp2.begin();
		if (tmp.curr->element.bought)
		{
			coins = coins + tmp.curr->element.theItem.cost;
			weight = weight - tmp.curr->element.theItem.weight;
			items.remove(tmp2);
			theHistory.remove(tmp);
		}
		else if (!tmp.curr->element.bought)
		{
			items.addHead(tmp.curr->element.theItem);
			coins = coins - tmp.curr->element.theItem.cost / 2;
			weight = weight + tmp.curr->element.theItem.weight;
			theHistory.remove(tmp);
		}
		system("cls");
	}
};

class Inventory
{
public:
	void AddItem(Item x)
	{
		int tmpCoins = coins - x.cost;
		int tmpWeight = weight + x.weight;
		if (tmpCoins < 0)
		{
			cout << "You cannot purchase that item" << '\n';
			system("pause");
		}
		else if (tmpWeight > maxWeight) 
		{
			cout << "You cannot purchase that item" << '\n';
			system("pause");
		}
		else
		{
			Transaction newT;
			newT.theItem = x;
			newT.bought = true;
			theHistory.addHead(newT);
			items.addHead(x);
			coins = tmpCoins;
			weight = tmpWeight;
			system("cls");
		}
	}
	void RemoveItem(Item x)
	{
		Transaction newT;
		x.name = convertToLower(x.name);
		SLLIter<Item> tmp(items);
		for (tmp.begin();!tmp.end(); ++tmp)
		{
			tmp.curr->element.name = convertToLower(tmp.curr->element.name);
			if (tmp.curr->element.name.compare(x.name) == 0)
			{
				newT.theItem = tmp.curr->element;
				newT.bought = false;
				theHistory.addHead(newT);
				coins = coins + x.cost / 2;
				weight = weight - x.weight;
				items.remove(tmp);
				return;
			}
		}
	}
	void Display()
	{
		cout << '\n' << '\t' << "Player Inventory" << '\n';
		cout << " Coins: " << coins << '\n';
		cout << " Weight: " << weight << '\n';
		cout << " Items in Inventory: " << '\n';
		if (items.size() > 0)
		{
			SLLIter<Item> tmp(items);
			while (!tmp.end())
			{
				cout << ' ' << tmp.curr->element.name << '\n';
				++tmp;
			}
		}
		else
			cout << '\n';
	}
};
class Store
{
public:
	void Load(const char * path)
	{
		ifstream itemIn;
		itemIn.open(path);
		while (true)
		{
			if (itemIn.eof())
			{
				break;
			}
			Item tmp;
			itemIn.ignore(1);
			itemIn >> tmp.type >> tmp.name >> tmp.cost >> tmp.weight;
			contents.append(tmp);
		}
	}
	void SortByType()
	{
		Item tmp, tmp2;
		for (unsigned int i = 0; i < contents.size(); i++)
		{
			for (unsigned int j = 0; j < contents.size(); j++)
			{
				if (contents[i].type < contents[j].type)
				{
					tmp = contents[i]; tmp2 = contents[j];
					contents[i] = tmp2; contents[j] = tmp;
				}
			}
		}
	}
	void SortByName()
	{
		Item tmp, tmp2;
		for (unsigned int i = 0; i < contents.size(); i++)
		{
			for (unsigned int j = 0; j < contents.size(); j++)
			{
				if (contents[i].name < contents[j].name)
				{
					tmp = contents[i]; tmp2 = contents[j];
					contents[i] = tmp2; contents[j] = tmp;
				}
			}
		}
	}
	void SortByPrice()
	{
		Item tmp, tmp2;
		for (unsigned int i = 0; i < contents.size(); i++)
		{
			for (unsigned int j = 0; j < contents.size(); j++)
			{
				if (contents[i].cost < contents[j].cost)
				{
					tmp = contents[i]; tmp2 = contents[j];
					contents[i] = tmp2; contents[j] = tmp;
				}
			}
		}
		
	}
	void SortByWeight()
	{
		Item tmp, tmp2;
		for (unsigned int i = 0; i < contents.size(); i++)
		{
			for (unsigned int j = 0; j < contents.size(); j++)
			{
				if (contents[i].weight < contents[j].weight)
				{
					tmp = contents[i]; tmp2 = contents[j];
					contents[i] = tmp2; contents[j] = tmp;
				}
			}
		}
	}
	void Display()
	{
		Store a;
		Inventory b;
		cout << '\t' << "Store Inventory" << '\n';
		cout << '\n';

		for (unsigned int i = 0; i < contents.size(); i++)
		{
			cout << ' ' << i + 1 << '.' << contents[i].type << '\t' << contents[i].name << '\t' << contents[i].cost << '\t' << contents[i].weight << '\n';
		}
		b.Display();
		cout << " 1. Sort the Store" << '\n';
		cout << " 2. Search for and Item in the Store" << '\n';
		cout << " 3. Buy an Item" << '\n';
		cout << " 4. Sell an Item" << '\n';
		cout << " 5. Undo Last Transaction" << '\n';
		cout << '\n';
		SLLIter<Item> tmp(items);
		string userSearch;
		string sellItem;
		int i;
		cin >> i;
		switch (i)
		{
		case SORTSTORE:
			cout << " How would you like to sort the Store?" << '\n';
			cout << " 1. By Type" << '\n';
			cout << " 2. By Name" << '\n';
			cout << " 3. By Cost" << '\n';
			cout << " 4. By Weight" << '\n';
			int j;
			cin >> j;
			switch (j)
			{
			case TYPE:
				a.SortByType();
				system("cls");
				a.Display();
				break;
			case NAME:
				a.SortByName();
				system("cls");
				a.Display();
				break;
			case COST:
				a.SortByPrice();
				system("cls");
				a.Display();
				break;
			case WEIGHT:
				a.SortByWeight();
				system("cls");
				a.Display();
				break;
			}
			break;
		case SEARCHSTORE:
			cout << " What would you like to search the Store for?" << '\n';
			cin >> userSearch;
			userSearch = convertToLower(userSearch);
			if (a.Search(userSearch) == true)
			{
				cout << " Yes we have that item." << '\n';
			}
			else
			{
				cout << " We do not have that item. " << '\n';
			}
			system("pause");
			system("cls");
			a.Display();
			break;
		case BUYITEM:
			cout << " Which Item would you like to buy?" << '\n';
			int i;
			cin >> i;
			switch (i)
			{
			case 1:
				b.AddItem(contents[0]);
				break;
			case 2:
				b.AddItem(contents[1]);
				break;
			case 3:
				b.AddItem(contents[2]);
				break;
			case 4:
				b.AddItem(contents[3]);
				break;
			case 5:
				b.AddItem(contents[4]);
				break;
			case 6:
				b.AddItem(contents[5]);
				break;
			case 7:
				b.AddItem(contents[6]);
				break;
			case 8:
				b.AddItem(contents[7]);
				break;
			case 9:
				b.AddItem(contents[8]);
				break;
			}
			system("cls");
			a.Display();
			break;
		case SELLITEM:
			cout << " Which Item would you like to sell?" << '\n';
			cin >> sellItem;
			for (tmp.begin();!tmp.end();++tmp)
			{
				tmp.curr->element.name = convertToLower(tmp.curr->element.name);
				if (tmp.curr->element.name.compare(sellItem) == 0)
				{
					b.RemoveItem(tmp.current());
					break;
				}
			}
			system("cls");
			a.Display();
			break;
		case UNDOTRANSACTION:
			TransactionManager newT;
			SLLIter<Transaction> tmp(theHistory);
			tmp.begin();
			newT.Undo();
			break;
		}


	}
	bool Search(string name)
	{
		for (unsigned int i = 0; i < contents.size(); i++)
		{
			contents[i].name = convertToLower(contents[i].name);
		}
		for (unsigned int i = 0; i < contents.size(); i++)
		{
			if (contents[i].name.compare(name) == 0)
			{
				return true;
			}
		}
		return false;
	}
};

