#include <iostream>
#include <thread>

#include <ncurses.h>

#include "Serial.hpp"

using namespace std;
using namespace IntroEE;

int main() {
	Serial klz("/dev/ttyACM0");
	string str;
	string lala = "123v";

	int j;

	int n = klz.read(str);
	if (lala.back() == 'f')
		j = atoi(lala.data());
	else j = 9999;

	cout << j << endl;

	cout << "Read " << n << ": " << str << endl;
	for(;;) {
		n = klz.read(str);

		cout << "Read " << n << ": " << str << endl;
	}

	return 0;
}
