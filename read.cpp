#include <iostream>
#include <fstream>
#include "render.hpp"

using namespace std;
int main()
{
	ifstream myfile;
	myfile.open( "out.ray");
	Object *obj = 0;
	while (!myfile.eof())
	{
		obj = Object::load0(myfile);
		if (!obj)
			break;
		cout << *obj << endl;
		delete obj;
	}
	myfile.close();
	return 0;
}
