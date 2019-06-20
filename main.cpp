#include "Project.h"
#include <fstream>
#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;
/*
Brady Hill
Schoolwork
Full Sail University
*/

bool storeOpen = true;

int main(int argc, char** argv)
{
	Store newStore;
	Inventory newInventory;
	newStore.Load("items.shp");
	while (storeOpen)
	{
		newStore.Display();
	}
}