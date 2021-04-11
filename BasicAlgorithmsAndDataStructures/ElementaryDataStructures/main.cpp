#include <list.h>
#include <iostream>

int main(int argc, char ** argv) {
	
	List<int> myList;
	myList.append(5);
	myList.append(7);
	myList.append(11);
	myList.append(3);

	List<int>::Iterator it;
	for (it = myList.begin(); it != myList.end(); ++it)
	{
		std::cout << *it << std::endl;
	}
	return 0;
}