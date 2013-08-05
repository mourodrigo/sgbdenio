//============================================================================
// Name        : sgbdenio.cpp
// Author      : Rodrigo Bueno Tomiosso & Andrey Baumhardt Ramos
// Version     :
// Copyright   : wtfpl
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <string>

using namespace std;

class Database{
	private:
		string name;
		string dir;
	public:
		string getName() const;
		void setName(string);

};

int main() {
	cout << "Hello" << endl; // prints Hello
	return 0;
}
