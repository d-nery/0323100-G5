#include <iostream>
#include <thread>
#include <mutex>

#include <ncurses.h>

#include "Serial.hpp"

using namespace std;
using namespace IntroEE;

static WINDOW* scr1;
static WINDOW* scr2;

static Serial klz("/dev/ttyACM0");

static int scr1X = 60;
static int scr1Y = 20;

static int scr2X = 40;
static int scr2Y = 20;

static double values[5]; // Tempertura, Ventoinha Ligada, Resistor Ligado,

static string klz_msg;
static mutex klz_msg_mtx;

void PainelDeControle() {
	string msg;

	for(;;) {
		wclear(scr1);
		box(scr1, 0, 0);

		msg = " Painel De Controle ";
		mvwprintw(scr1, 0, scr1X/2 - msg.length()/2, msg.data());

		klz_msg_mtx.lock();
		msg = "Temperatura: " + to_string(values[0]) + " °C";
		mvwprintw(scr1, 2, 1, msg.data());

		msg = "Ventilador: " + to_string(bool(values[1]));
		mvwprintw(scr1, 3, 1, msg.data());

		msg = "Resistor: " + to_string(bool(values[2]));
		mvwprintw(scr1, 4, 1, msg.data());

		msg = "LED: " + to_string(bool(values[3]));
		mvwprintw(scr1, 5, 1, msg.data());

		// msg = "Potenciometro: " + to_string(values[4]);
		// mvwprintw(scr1, 6, 1, msg.data());

		msg = klz_msg;
		mvwprintw(scr1, scr1Y - 2, 1, msg.data());
		klz_msg_mtx.unlock();

		wrefresh(scr1);

		usleep(100 * 1000);
	}
}

void Instrucoes() {
	string msg;

	wclear(scr2);
	box(scr2, 0, 0);

	msg = " Instrucoes ";
	mvwprintw(scr2, 0, scr2X/2 - msg.length()/2, msg.data());

	msg = "Aperte s para ligar";
	mvwprintw(scr2, 2, 1, msg.data());

	msg = "Aperte p para parar";
	mvwprintw(scr2, 3, 1, msg.data());

	msg = "Aperte v para ligar ventoinha";
	mvwprintw(scr2, 4, 1, msg.data());

	msg = "Aperte w para desligar ventoinha";
	mvwprintw(scr2, 5, 1, msg.data());

	msg = "Aperte l para alternar led";
	mvwprintw(scr2, 6, 1, msg.data());

	msg = "Aperte q para sair";
	mvwprintw(scr2, scr2Y - 2, 1, msg.data());

	wrefresh(scr2);

	usleep(100 * 1000);
}

void reader() {
	int n;
	string temp;

	for (;;) {
		n = klz.read(temp);
		if (n > 0) {
			klz_msg_mtx.lock();
			switch(temp.back()) {
			case 't': // Temperatura
				values[0] = atof(temp.data());
				klz_msg = "";
				break;

			case 'v': // Ventoinha
				values[1] = atof(temp.data());
				klz_msg = "";
				break;

			case 'r': // Resistor
				values[2] = atof(temp.data());
				klz_msg = "";
				break;

			case 'l': // LED
				values[3] = atof(temp.data());
				klz_msg = "";
				break;

			case 'p': // Potenciometro
				values[4] = atof(temp.data());
				klz_msg = "";
				break;

			case 'm': // Mensagem comum
				temp.pop_back();
				klz_msg = temp;
			}
			klz_msg_mtx.unlock();
		}
		usleep(10 * 1000);
	}
}

int main(int argc, char** argv) {
	initscr();
	raw();
	noecho();
	// keypad(stdscr, TRUE);

	for (int i = 0; i < 5; i++)
		values[i] = 0;

	string msg;
	char c;

	scr1 = newwin(scr1Y, scr1X, LINES/2 - scr1Y/2, COLS/2 - scr1X/2 - scr2X + 2);
	box(scr1, 0, 0);

	scr2 = newwin(scr2Y, scr2X, LINES/2 - scr2Y/2, COLS/2 - scr1X/2 + scr1X - 2);
	box(scr2, 0, 0);

	msg = "*************************************************";
	mvprintw(1, COLS/2 - msg.length()/2, msg.data());
	msg = "Reciclador de plástico";
    mvprintw(2, COLS/2 - msg.length()/2, msg.data());
	msg = "";
    mvprintw(3, COLS/2 - msg.length()/2, msg.data());
	msg = "0323100 - Introducao a Engenharia Eletrica";
	mvprintw(4, COLS/2 - msg.length()/2, msg.data());
	msg = "Grupo 5";
	mvprintw(5, COLS/2 - msg.length()/2, msg.data());
	msg = "*************************************************";
	mvprintw(6, COLS/2 - msg.length()/2, msg.data());


	refresh();
	wrefresh(scr1);
	wrefresh(scr2);

	Instrucoes();

	thread tela1(PainelDeControle);
	thread tela2(reader);

	tela1.detach();
	tela2.detach();

	for (;;) {
		c = getch();
		switch (c) {
		case 'q': endwin(); return 0;
		default:
			string str = to_string(c);
			klz.write(str);
		}
	}

	endwin();

	return 0;
}
