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

#pragma once

#include <string>

#include <ncurses.h>

namespace IntroEE {
	class Interface {
		WINDOW* tela1;
		WINDOW* tela2;
		std::string msg;
		std::string plastAtual;
		int meiox;
		int x;

	public:
		Interface();

		void setPlastico(std::string plast);

		void printTheBox();
		void telaInicial(std::string aviso);
		void telaControle(float temp, int minutos, bool fan, bool buzzer, bool rele, std::string aviso);
	};
}
