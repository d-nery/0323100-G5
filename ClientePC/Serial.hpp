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

#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <cstdio>
#include <string>

#include <sys/ioctl.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

namespace IntroEE {
	class Serial {
	private:
		int fd;
		struct termios tty;

	public:
		Serial(std::string dev);
		~Serial();
		int read(std::string& str);
		void write(std::string data);
	};
}
