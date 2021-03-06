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

/**
 * Programa principal da KL25Z
 *
 * Inicia a camara termica
 */

#include "Camara.hpp"

using namespace IntroEE;

int main(void) {
    Camara camara;

    while (1) {
        camara.waitStartCommand();
        camara.start();
        camara.stop();
    }
}
