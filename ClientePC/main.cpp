/**
Escola Politecnica da Universidade de Sao Paulo
0323100 - Introducao a Engenharia Eletrica - 2015

Projeto de Câmara Térmica

Grupo 5
    Daniel Nery Silva de Oliveira - 9349051
    Daniel Seiji Tsutsumi         - 9349005
    Mariana Sartori Testa         - 9348773
    Mateus Almeida Barbosa        - 9349072
*/

#include <iostream>
#include <thread>
#include <chrono>
#include <atomic>
#include <mutex>

#include <ncurses.h>

#include "Interface.hpp"
#include "Serial.hpp"

using namespace std;
using namespace chrono;
using namespace IntroEE;

Serial klz("/dev/ttyACM0");

static float values[] = {0., 0., 0., 0.}; // Tempertura, Ventoinha Ligada, Resistor Ligado, buzzer Ligado

static atomic<bool> inicio(false);

static string klz_msg;
static mutex klz_msg_mtx;

void reader() {
try {
	int n;
	string temp;

	for (;;) {
		n = klz.read(temp);
		if (n > 0) {
			klz_msg_mtx.lock();
			switch (temp.back()) {
			case 't': // Temperatura
				values[0] = atof(temp.data());
				// klz_msg = "";
				break;

			case 'v': // Ventoinha
				values[1] = atof(temp.data());
				// klz_msg = "";
				break;

			case 'r': // Resistor
				values[2] = atof(temp.data());
				// klz_msg = "";
				break;

			case 'b': // buzzer
				values[3] = atof(temp.data());
				// klz_msg = "";
				break;

			case 'm': // Mensagem comum
				temp.pop_back();
				klz_msg = temp;

			// case 'i':
				// inicio.store(true);
			// 	klz_msg = "";
			}
			klz_msg_mtx.unlock();
		}
		usleep(10 * 1000);
	}
} catch (out_of_range& e) {
	endwin();
	cerr << "Ocorreu um erro: " << e.what() << "\nPor favor, verifique a conexão recomece o programa\n";
	exit(-1);
}
}

int main(int argc, char** argv) {
try {
	initscr();
	raw();
	noecho();
	// keypad(stdscr, TRUE);

	int c, min;
	string str;

	Interface interface;

	thread _reader(reader);

	_reader.detach();

	for (;;) {
		klz_msg_mtx.lock();
		interface.telaInicial(klz_msg);
		klz_msg_mtx.unlock();
		timeout(100);
		c = getch();
		switch(tolower(c)) {
		case 'q':
			endwin();
			return 0;

		case 'a':
			interface.setPlastico("parafina");
			str = to_string(c);
			klz.write(str);
			break;

		case 'b':
			interface.setPlastico("garrafa PET");
			str = to_string(c);
			klz.write(str);
			break;

		case 'c':
			interface.setPlastico("sacola plástica");
			str = to_string(c);
			klz.write(str);
			break;

		case 'd':
			interface.setPlastico("copo descartável");
			str = to_string(c);
			klz.write(str);
			break;

		default:
			continue;
		}

		inicio.store(false);

		timeout(500);
		auto begin = high_resolution_clock::now();
		auto now = high_resolution_clock::now();

		for (;;) {
			now = high_resolution_clock::now();
			min = duration_cast<minutes>(now - begin).count();
			klz_msg_mtx.lock();
			interface.telaControle(values[0], min, values[1], values[3], values[2], klz_msg);
			klz_msg_mtx.unlock();

			c = getch();
			switch (tolower(c)) {
				case 'z': endwin(); return 0;
				case 'q': inicio.store(true);
				default:
					str = to_string(c);
					klz.write(str);
			}
			usleep(500 * 1000);

			if (inicio.load()) break;
		}
	}

} catch (out_of_range& e) {
	endwin();
	cerr << "Ocorreu um erro: " << e.what() << "\nPor favor, verifique a conexão recomece o programa\n";
	exit(-1);
}
	endwin();

	return 0;
}
