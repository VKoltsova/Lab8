#include "list.h"
#include "point.h"
#include <windows.h>
#include <iostream>
using namespace std;

int main() {
	Point<LinkedList<char>> list_p1(new LinkedList<char>);
	list_p1->addNode('1');
	list_p1->addNode('2');
	list_p1->print();
	list_p1->removeNode();
	list_p1->addNode('3');
	cout << list_p1;

	Point<LinkedList<int>> list_p2(new LinkedList<int>);
	list_p2->addNode(1);
	list_p2->addNode(0);
	cout << list_p2;
	
	Point<LinkedList<int>> list_p3(new LinkedList<int>);
	cout << "Compare: " << ((list_p2 == list_p3) ? "True" : "False") << endl;
	list_p3->addNode(5);
	list_p3->addNode(10);
	cout << "Compare: " << ((list_p2 == list_p3) ? "True" : "False") << endl;

	system("pause");
	return 0;
}