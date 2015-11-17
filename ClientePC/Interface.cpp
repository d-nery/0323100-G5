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

#include "Interface.hpp"

#include "temperaturas.h"

namespace IntroEE {
    Interface::Interface() {
        meiox = COLS/2;
        x = 0;
    }

    void Interface::setPlastico(std::string plast) {
        plastAtual = plast;
    }

    void Interface::printTheBox() {
        x = 5;

        msg = "....................8.............................................................................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = "...................88.............................................................................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = "..................888.............................................................................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888.............................................................................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888.............................................................................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888.............................................................................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888.............................................................................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888..8888.8..8.8888.............................................................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888...88..8888.8~~..............................................................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888...88..8..8.8888.............................................................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888.............................................................................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................888888888888888888888..8888888888888888888.888.................888...............";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................888888888888888888888..88888888888888888888..888.............888.................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888..............888..888...............888...888.........888...................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888..............888..888...............888.....888.....888.....................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888..............888..888...............888.......888.888.......................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888..............888..888...............888.........888.........................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888..............888..888...............888.......888.888.......................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888..............888..888...............888.....888.....888.....................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................88888888888888888888....88888888888888888888...888.........888...................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
        msg = ".................8888888888888888888......8888888888888888888.888.............888.................";
        mvprintw(x++, meiox - msg.length()/2, msg.data());
    }

    void Interface::telaInicial(std::string aviso) {
        clear();
        printTheBox();
        refresh();

        int meioTelaX = msg.length()/2;

        tela1 = newwin(15, msg.length(), x + 5, meiox - msg.length()/2);
        box(tela1, 0, 0);

        msg = " Escolha um plastico para iniciar ";
        mvwprintw(tela1, 0, meioTelaX - msg.length()/2, msg.data());

        x = 2;

        msg = "A) Parafina         - Ponto de Fusão: " + std::to_string(int(TEMP_PARAFINA)) + "°C | Tempo Médio: 30 minutos.";
        mvwprintw(tela1, x++, 1, msg.data()); x++;

        msg = "B) Garrafa PET      - Ponto de Fusão: " + std::to_string(int(TEMP_PET)) + "°C | Tempo Médio: ?";
        mvwprintw(tela1, x++, 1, msg.data());

        msg = "C) Sacola Plástica  - Ponto de Fusão: " + std::to_string(int(TEMP_SACOLA)) + "°C | Tempo Médio: ?";
        mvwprintw(tela1, x++, 1, msg.data());

        msg = "D) Copo Descartável - Ponto de Fusão: " + std::to_string(int(TEMP_COPO)) + "°C | Tempo Médio: ?";
        mvwprintw(tela1, x++, 1, msg.data());

        mvwprintw(tela1, 13, 1, aviso.data());

        wrefresh(tela1);
        refresh();
    }

    void Interface::telaControle(float temp, int minutos, bool fan, bool buzzer, bool rele, std::string aviso) {
        clear();
        printTheBox();
        refresh();

        int tela1x = msg.length()/3 + 5;
        int tela2x = 2*msg.length()/3 - 10;

        tela1 = newwin(15, tela1x, x + 5, meiox - msg.length()/2);
        tela2 = newwin(15, tela2x, x + 5, meiox - msg.length()/2 + tela1x + 6);
        box(tela1, 0, 0);
        box(tela2, 0, 0);

        msg = " Controle ";
        mvwprintw(tela1, 0, tela1x/2 - msg.length()/2, msg.data());

        msg = " Observacoes ";
        mvwprintw(tela2, 0, tela2x/2 - msg.length()/2, msg.data());

        x = 2;

        mvwprintw(tela1, x++, 1, "Temperatura da camara: %.1f", temp); x++;
        msg = std::string("Ventoinha: ") + std::string((fan ? "ligada" : "desligada"));
        mvwprintw(tela1, x++, 1, msg.data());
        msg = std::string("Buzzer: ") + std::string((buzzer ? "ligado" : "desligado"));
        mvwprintw(tela1, x++, 1, msg.data());
        msg = std::string("Aquecimento: ") + std::string((rele ? "ligado" : "desligado"));
        mvwprintw(tela1, x++, 1, msg.data());

        msg = "Derretendo " + plastAtual;
        mvwprintw(tela2, 2, tela2x/2 - msg.length()/2, msg.data());

        x = 4;
        mvwprintw(tela2, x++, 1, "Pressione d para comandos manuais:");
        mvwprintw(tela2, x++, 1, "  q - desliga e volta para selecao");
        mvwprintw(tela2, x++, 1, "  v - alterna a ventoinha");
        mvwprintw(tela2, x++, 1, "  b - alterna o buzzer");
        mvwprintw(tela2, x++, 1, "  r - alterna a resistencia");
        mvwprintw(tela2, x++, 1, "  s - volta para o automatico");

        mvwprintw(tela2, 12, 1, aviso.data());
        msg = "Tempo Decorrido " + std::to_string(minutos) + " min";
        mvwprintw(tela2, 13, 1, msg.data());

        wrefresh(tela1);
        wrefresh(tela2);
        refresh();
    }
}
