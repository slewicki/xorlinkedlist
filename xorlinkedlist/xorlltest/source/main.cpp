/*
Application to test XOR linked list library
Created by Sebastian Lewicki
Date 01/07/2018
*/

#include <iostream>
using namespace std;

#include "xorlinkedlist.h"

int main()
{
	xorlinkedlist<int> intList;
	intList.insert(1);
	intList.insert(2);
	intList.insert(3);
	intList.insert(4);
	intList.insert(5);
	intList.insert(0, false);

	intList.iterateFromHead();
	for (size_t i = 0; i < intList.getSize(); i++)
	{
		int data = -1;
		intList.getData(&data);
		intList.move();

		cout << "Int Value: " << data << endl;
	}

	cout << "\nReverse traversal" << endl;
	intList.iterateFromTail();
	for (int i = (int)intList.getSize() - 1; i >= 0; i--)
	{
		int data = -1;
		intList.getData(&data);
		intList.move();

		cout << "Int Value: " << data << endl;
	}

	intList.clear();

	return 0;
}