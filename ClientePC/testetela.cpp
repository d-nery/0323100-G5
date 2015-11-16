#include <cctype>
#include <chrono>

#include <ncurses.h>

#include "Interface.hpp"

using namespace IntroEE;
using namespace std;
using namespace chrono;


int main() {
	int c, min, x = 1;

	initscr();
	raw();
	noecho();

	Interface interface;
	interface.telaInicial();

	c = getch();
	switch(std::tolower(c)) {
		case 'q': endwin(); return 0;
		case 'a': interface.setPlastico("parafina"); break;
		case 'b': interface.setPlastico("garrafa PET"); break;
		case 'c': interface.setPlastico("sacola plástica"); break;
		case 'd': interface.setPlastico("copodescartável"); break;
	}

	auto begin = high_resolution_clock::now();

	for(;;) {
		auto now = high_resolution_clock::now();
		min = duration_cast<minutes>(now - begin).count();
		interface.telaControle(x++, min, 0, 0, 0, "mensagem");
		c = getch();
		switch(c) {
			case 'q': endwin(); return 0;
		}
	}

	endwin();
	return 0;
}
