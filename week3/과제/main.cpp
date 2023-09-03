#include "Str.h"

int main(){
	Str a("I'm a girl");
	std::cout << a.contents();
	a = "I'm a boy\n";
	std::cout << a.contents();
	std::cout << a.compare("I'm a a") << std::endl;
	return 0;
}
